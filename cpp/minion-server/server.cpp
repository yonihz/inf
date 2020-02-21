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

#include "server.hpp"
#include "logger.hpp"
#include "singleton.hpp"
#include "fd_listener.hpp"
#include "reactor.hpp"

#define UNUSED(x) (void)(x)

namespace ilrd
{

/******************************************************************************/
/**** ServerConsole ***********************************************************/
/******************************************************************************/

ServerConsole::ServerConsole(int fd_, Reactor *reactor_)
    : m_cmd_manager(reactor_), m_console_fd(fd_), m_reactor(reactor_) {}

void ServerConsole::AddToReactor()
{
    m_reactor->AddFD(m_console_fd.GetFD(), Reactor::READ, *this);
}

void ServerConsole::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    char str[MAXDATASIZE];

    fgets(str, MAXDATASIZE, stdin);

    try
    {
        m_cmd_manager.RunCommand(str);
    }
    catch(const InvalidKey& e)
    {
        logger.Log(Logger::ERROR, std::string(e.what()) + "\n");
    }
    
    return;
}

/******************************************************************************/
/**** ConsoleCommandManager ***************************************************/
/******************************************************************************/

ConsoleCommandManager::ConsoleCommandManager(Reactor *reactor_)
    : m_reactor(reactor_)
{
    m_factory.Add("exit\n", CreatorConsoleExitCmd);
    m_factory.Add("+\n", CreatorConsolePlusCmd);
    m_factory.Add("-\n", CreatorConsoleMinusCmd);
    m_factory.Add("ping\n", CreatorConsolePingCmd);
    m_factory.Add("cout\n", CreatorConsoleOutputCoutCmd);
}

void ConsoleCommandManager::RunCommand(std::string str_)
{
    (*m_factory.Create(str_))(m_reactor);
}

void ConsoleCommandManager::AddCommand(
    std::string key_, 
    boost::shared_ptr<ConsoleCommand>(*creator_)(void))
{
    m_factory.Add(key_, creator_);
}

/******************************************************************************/
/**** ConsoleFD ***************************************************************/
/******************************************************************************/

ConsoleFD::ConsoleFD(int fd_)
    : m_fd(fd_) {}

int ConsoleFD::GetFD()
{
    return m_fd;
}

/******************************************************************************/
/**** UDPServer ***************************************************************/
/******************************************************************************/

UDPServer::UDPServer(const char *ip_, int port_, CommandManager &cmd_manager_, Reactor *reactor_)
    : m_reply_len(), m_cmd_manager(cmd_manager_), m_socket(new UDPServerSocket(ip_, port_)), m_reactor(reactor_)
{
    m_reply_len[0] = READ_REPLY_LEN;
    m_reply_len[1] = WRITE_REPLY_LEN;    
}

int UDPServer::Init()
{
    return m_socket->Init();
}

void UDPServer::AddToReactor()
{
    m_reactor->AddFD(m_socket->GetFD(), Reactor::READ, *this);
}

void UDPServer::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    int status;
    char request_buffer[BUFFER_SIZE];
    struct sockaddr client_addrinfo;
    socklen_t client_addrlen = sizeof(client_addrlen);

    status = recvfrom(m_socket->GetFD(), request_buffer, BUFFER_SIZE, MSG_CONFIRM, &client_addrinfo, &client_addrlen);

    if (-1 == status)
    {
       logger.Log(Logger::ERROR, "recvfrom error: " + std::string(strerror(errno)) + "\n");
    }

    try
    {
        m_cmd_manager.RunCommand(request_buffer[REQUEST_TYPE_BYTE], request_buffer);
    }
    catch(const InvalidKey& e)
    {
        logger.Log(Logger::ERROR, std::string(e.what()) + "\n");
        return;
    }

    status = sendto(m_socket->GetFD(), request_buffer, m_reply_len[(size_t)request_buffer[REQUEST_TYPE_BYTE]], MSG_WAITALL, &client_addrinfo, client_addrlen);

    if (-1 == status)
    {
       logger.Log(Logger::ERROR, "sendto error: " + std::string(strerror(errno)) + "\n");
    }
}

/******************************************************************************/
/**** UDPServerSocket *********************************************************/
/******************************************************************************/

UDPServerSocket::UDPServerSocket(const char *ip_, int port_)
    : m_ip(ip_), m_port(port_) {}

UDPServerSocket::~UDPServerSocket()
{
    CloseSocket();
}

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

/******************************************************************************/
/**** TCPServer ***************************************************************/
/******************************************************************************/

TCPServer::TCPServer(const char *ip_, int port_, CommandManager &cmd_manager_, Reactor *reactor_)
    : m_cmd_manager(cmd_manager_), 
    m_socket(new TCPServerSocket(ip_, port_)), 
    m_reactor(reactor_) {}

int TCPServer::Init()
{
    return m_socket->Init();
}

void TCPServer::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    int new_sockfd;
    struct sockaddr_storage client_ai;
    socklen_t client_addrlen;
    client_addrlen = sizeof(client_addrlen);

    new_sockfd = accept(m_socket->GetFD(), (struct sockaddr *)&client_ai, &client_addrlen);

    if (new_sockfd == -1)
    {
        logger.Log(Logger::ERROR, "accept: " + std::string(strerror(errno)) + "\n");
        return;
    }

    TCPConnection tcp_connection(new_sockfd, this->m_cmd_manager, this->m_reactor);
    tcp_connection.AddToReactor();
}

void TCPServer::AddToReactor()
{
    m_reactor->AddFD(m_socket->GetFD(), Reactor::READ, *this);
}

/******************************************************************************/
/**** TCPServerSocket *********************************************************/
/******************************************************************************/

TCPServerSocket::TCPServerSocket(const char *ip_, int port_)
    : m_ip(ip_), m_port(port_) {}

TCPServerSocket::~TCPServerSocket()
{
    CloseSocket();
}

int TCPServerSocket::Init()
{
    Logger &logger = *(Singleton<Logger>::Instance());

    int status;
    status = CreateSocket();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "TCP server: failed to bind\n");
        return -1;
    } 

    status = Listen();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "TCP server listen error\n");
        return -1;
    }

    logger.Log(Logger::INFO, "TCP server: waiting for connections...\n");
    return 0;
}

int TCPServerSocket::GetFD()
{
    return m_sockfd;
}

void TCPServerSocket::CloseSocket()
{
    close(m_sockfd);
}

int TCPServerSocket::CreateSocket()
{
    struct addrinfo *server_ai;
    InitAddrinfo(NULL, m_port, AF_UNSPEC, SOCK_STREAM, AI_PASSIVE, &server_ai);
    m_sockfd = TCPServerBindSocket(server_ai);
    return m_sockfd;
}

int TCPServerSocket::Listen()
{
    return listen(m_sockfd, BACKLOG);
}

/******************************************************************************/
/**** TCPConnection ***********************************************************/
/******************************************************************************/

TCPConnection::TCPConnection(int sockfd_, CommandManager cmd_manager_, Reactor *reactor_)
    : m_socket(new TCPConnectionSocket(sockfd_)), 
    m_cmd_manager(cmd_manager_),
    m_reactor(reactor_) {}

void TCPConnection::AddToReactor()
{
    m_reactor->AddFD(m_socket->GetFD(), Reactor::READ, *this);
}

void TCPConnection::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    char buff[MAXDATASIZE];
    ssize_t nbytes_sent, nbytes_rcvd;
    const char *pong_msg = "Pong";
    size_t len_pong_msg = strlen(pong_msg);

    nbytes_rcvd = recv(m_socket->GetFD(), buff, MAXDATASIZE, 0);
    if (nbytes_rcvd == 0)
    {
        logger.Log(Logger::DEBUG, "Closing TCP connection\n");
        m_reactor->RemoveFD(m_socket->GetFD(), Reactor::READ);
        return;
    }

    if (nbytes_rcvd == -1)
    {
        logger.Log(Logger::ERROR, "TCP server recv error: " + std::string(strerror(errno)) + "\n");
    }

    buff[nbytes_rcvd] = '\0';

    logger.Log(Logger::DEBUG, "TCP server: received: " + std::string(buff) + "\n");

    if (strcmp(buff, "Ping") == 0)
    {
        nbytes_sent = send(m_socket->GetFD(), pong_msg, len_pong_msg, 0);

        if (nbytes_sent == -1)
        {
            logger.Log(Logger::ERROR, "TCP server send error\n");
        }
    }
}

/******************************************************************************/
/**** TCPConnectionSocket *****************************************************/
/******************************************************************************/

TCPConnectionSocket::TCPConnectionSocket(int sockfd_)
    : m_sockfd(sockfd_) {}

TCPConnectionSocket::~TCPConnectionSocket()
{
    CloseSocket();
}

int TCPConnectionSocket::GetFD()
{
    return m_sockfd;
}

void TCPConnectionSocket::CloseSocket()
{
    close(m_sockfd);
}

} //namespace ilrd
