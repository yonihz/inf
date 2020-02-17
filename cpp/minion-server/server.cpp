#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <errno.h>
#include <dlfcn.h>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast; 
using boost::bad_lexical_cast;

#include "server.hpp"
#include "logger.hpp"
#include "singleton.hpp"
#include "fd_listener.hpp"
#include "reactor.hpp"

#define UNUSED(x) (void)(x)

namespace ilrd
{

ServerConsole::ServerConsole(int fd_, Reactor *reactor_)
    : m_cmd_manager(reactor_), m_console_fd(fd_), m_reactor(reactor_) {}

void ServerConsole::AddToReactor()
{
    m_reactor->AddFD(m_console_fd.GetFD(), Reactor::READ, *this);
}

void ServerConsole::operator()(void)
{
    char str[MAXDATASIZE];

    fgets(str, MAXDATASIZE, stdin);

    try
    {
        m_cmd_manager.RunCommand(str);
    }
    catch(const InvalidKey& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return;
}

ConsoleCmdManager::ConsoleCmdManager(Reactor *reactor_)
    : m_reactor(reactor_)
{
    m_factory.Add("exit\n", CreatorConsoleExitCmd);
    m_factory.Add("+\n", CreatorConsolePlusCmd);
    m_factory.Add("-\n", CreatorConsoleMinusCmd);
    m_factory.Add("ping\n", CreatorConsolePingCmd);
    m_factory.Add("cout\n", CreatorConsoleOutputCoutCmd);
}

void ConsoleCmdManager::RunCommand(std::string str_)
{
    (*m_factory.Create(str_))(m_reactor);
}

void ConsoleCmdManager::AddCommand(
    std::string key_, 
    boost::shared_ptr<ConsoleCommand>(*creator_)(void))
{
    m_factory.Add(key_, creator_);
}

ConsoleFD::ConsoleFD(int fd_)
    : m_fd(fd_) {}

int ConsoleFD::GetFD()
{
    return m_fd;
}

UDPServer::UDPServer(const char *ip_, int port_, Reactor *reactor_)
    : m_reply_len(), m_cmd_manager(reactor_), m_socket(ip_, port_), m_reactor(reactor_)
{
    m_reply_len[0] = READ_REPLY_LEN;
    m_reply_len[1] = WRITE_REPLY_LEN;    
}

UDPServer::~UDPServer()
{
    m_socket.CloseSocket();
}

int UDPServer::Init()
{
    return m_socket.Init();
}

void UDPServer::AddToReactor()
{
    m_reactor->AddFD(m_socket.GetFD(), Reactor::READ, *this);
}

void UDPServer::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    int status;
    char request_buffer[BUFFER_SIZE];
    struct sockaddr client_addrinfo;
    socklen_t client_addrlen = sizeof(client_addrlen);

    status = recvfrom(m_socket.GetFD(), request_buffer, BUFFER_SIZE, MSG_CONFIRM, &client_addrinfo, &client_addrlen);

    if (-1 == status)
    {
       logger.Log(Logger::ERROR, "recvfrom error: " + std::string(strerror(errno)) + "\n");
    }

    m_cmd_manager.RunCommand(request_buffer[REQUEST_TYPE_BYTE], request_buffer);

    status = sendto(m_socket.GetFD(), request_buffer, m_reply_len[(size_t)request_buffer[REQUEST_TYPE_BYTE]], MSG_WAITALL, &client_addrinfo, client_addrlen);

    if (-1 == status)
    {
       logger.Log(Logger::ERROR, "sendto error: " + std::string(strerror(errno)) + "\n");
    }
}


UDPServerSocket::UDPServerSocket(const char *ip_, int port_)
    : m_ip(ip_), m_port(port_) {}

void UDPServerSocket::CloseSocket()
{
    close(m_sockfd);
}

int UDPServerSocket::GetFD()
{
    return m_sockfd;
}

int UDPServerSocket::Init()
{
    Logger &logger = *(Singleton<Logger>::Instance());
    
    struct addrinfo *server_ai;
    InitAddrinfo(m_ip, m_port, AF_UNSPEC, SOCK_DGRAM, AI_PASSIVE, &server_ai);

    m_sockfd = UDPServerBindSocket(server_ai);

    if (m_sockfd == -1)
    {
        logger.Log(Logger::ERROR, "UDP server: failed to bind\n");
        return -1;
    }

    return m_sockfd;
}

UDPCmdManager::UDPCmdManager(Reactor *reactor_)
    : m_reactor(reactor_), m_factory()
{
    void *handle_read_request_cmd;
    boost::shared_ptr<Command> (*CreatorReadRequestCmd)();
    char (*GetKeyReadRequestCmd)(void);

    void *handle_write_request_cmd;
    boost::shared_ptr<Command> (*CreatorWriteRequestCmd)();
    char (*GetKeyWriteRequestCmd)(void);
    char *error;

    handle_read_request_cmd = dlopen ("./libcommand_read_request.so", RTLD_LAZY);
    if (!handle_read_request_cmd) {
        fputs (dlerror(), stderr);
        return;
    }

    CreatorReadRequestCmd = (boost::shared_ptr<Command>(*)()) dlsym(handle_read_request_cmd, "Creator");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        return;
    }

    GetKeyReadRequestCmd = (char(*)(void)) dlsym(handle_read_request_cmd, "GetKey");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        return;
    }

    handle_write_request_cmd = dlopen ("./libcommand_write_request.so", RTLD_LAZY);
    if (!handle_write_request_cmd) {
        fputs (dlerror(), stderr);
        return;
    }

    CreatorWriteRequestCmd = (boost::shared_ptr<Command>(*)()) dlsym(handle_write_request_cmd, "Creator");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        return;
    }

    GetKeyWriteRequestCmd = (char(*)(void)) dlsym(handle_write_request_cmd, "GetKey");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        return;
    }

    m_factory.Add((int)(*GetKeyReadRequestCmd)(), CreatorReadRequestCmd);
    m_factory.Add((int)(*GetKeyWriteRequestCmd)(), CreatorWriteRequestCmd);   
}

void UDPCmdManager::RunCommand(char c_, char *buffer_)
{
    (*m_factory.Create(c_))(buffer_);
}

void UDPCmdManager::AddCommand(char c_, boost::shared_ptr<Command>(*creator_)(void))
{
    m_factory.Add((int)c_, creator_);
}

} //namespace ilrd

// TCPServer::TCPServer(const char *ip_, int port_, Reactor *reactor_)
//     : m_cmd_manager(reactor_), m_socket(ip_, port_), m_reactor(reactor_) {}

// TCPListener::TCPListener(int port_, Reactor *reactor_)
//     : m_port(port_), m_sockfd() , m_connections(new std::set<int>), m_reactor(reactor_) {}

// void TCPListener::CloseSocket()
// {
//     close(m_sockfd);
// }

// void TCPListener::CloseAllConnections()
// {
//     std::set<int>::iterator it;
//     std::set<int>::iterator it_end = m_connections->end();
//     for (it = m_connections->begin(); it != it_end; ++it)
//     {
//         close(*it);
//     }
// }

// void TCPListener::CloseConnection(int sockfd)
// {
//     m_connections->erase(sockfd);
//     close(sockfd);
// }

// int TCPListener::CreateSocket()
// {
//     struct addrinfo *server_ai;
//     InitAddrinfo(NULL, m_port, AF_UNSPEC, SOCK_STREAM, AI_PASSIVE, &server_ai);
//     m_sockfd = TCPServerBindSocket(server_ai);
//     return m_sockfd;
// }

// int TCPListener::GetSocket()
// {
//     return m_sockfd;
// }

// int TCPListener::Listen()
// {
//     return listen(m_sockfd, BACKLOG);
// }

// int TCPListener::Init()
// {
//     Logger &logger = *(Singleton<Logger>::Instance());

//     int status;
//     status = CreateSocket();

//     if (status == -1)
//     {
//         logger.Log(Logger::ERROR, "TCP server: failed to bind\n");
//         return -1;
//     } 

//     status = Listen();

//     if (status == -1)
//     {
//         logger.Log(Logger::ERROR, "TCP server listen error\n");
//         return -1;
//     }

//     logger.Log(Logger::INFO, "TCP server: waiting for connections...\n");
//     return 0;
// }

// void TCPListener::operator()(void)
// {
//     Logger &logger = *(Singleton<Logger>::Instance());
//     int new_sockfd;
//     struct sockaddr_storage client_ai;
//     socklen_t client_addrlen;
//     client_addrlen = sizeof(client_addrlen);

//     new_sockfd = accept(m_sockfd, (struct sockaddr *)&client_ai, &client_addrlen);

//     if (new_sockfd == -1)
//     {
//         logger.Log(Logger::ERROR, "accept: " + std::string(strerror(errno)) + "\n");
//         return;
//     }

//     m_connections->insert(new_sockfd);

//     m_reactor->AddFD(
//         new_sockfd,
//         Reactor::READ,
//         TCPRequestMgr(new_sockfd, m_reactor, this));
// }

// TCPRequestMgr::TCPRequestMgr(int sockfd_, Reactor *reactor_, TCPListener *tcp_listener_)
//     : m_sockfd(sockfd_), m_reactor(reactor_), m_tcp_listener(tcp_listener_) {}

// void TCPRequestMgr::operator()(void)
// {
//     Logger &logger = *(Singleton<Logger>::Instance());
//     char buff[MAXDATASIZE];
//     ssize_t nbytes_sent, nbytes_rcvd;
//     const char *pong_msg = "Pong";
//     size_t len_pong_msg = strlen(pong_msg);

//     nbytes_rcvd = recv(m_sockfd, buff, MAXDATASIZE, 0);
//     if (nbytes_rcvd == 0)
//     {
//         logger.Log(Logger::DEBUG, "Closing TCP connection\n");
//         m_tcp_listener->CloseConnection(m_sockfd);
//         m_reactor->RemoveFD(m_sockfd, Reactor::READ);
//         return;
//     }

//     if (nbytes_rcvd == -1)
//     {
//         logger.Log(Logger::ERROR, "TCP server recv error: " + std::string(strerror(errno)) + "\n");
//     }

//     buff[nbytes_rcvd] = '\0';

//     logger.Log(Logger::DEBUG, "TCP server: received: " + std::string(buff) + "\n");

//     if (strcmp(buff, "Ping") == 0)
//     {
//         nbytes_sent = send(m_sockfd, pong_msg, len_pong_msg, 0);

//         if (nbytes_sent == -1)
//         {
//             logger.Log(Logger::ERROR, "TCP server send error\n");
//         }
//     }
// }