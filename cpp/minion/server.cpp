#include <stdio.h>
#include <string.h>
#include <string>
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

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast; 
using boost::bad_lexical_cast;

#include "server.hpp"
#include "logger.hpp"
#include "singleton.hpp"
#include "fd_listener.hpp"
#include "reactor.hpp"

#define UNUSED(x) (void)(x)

#define MAXDATASIZE 100

namespace ilrd
{

Server::Server(int tcp_port, int udp_port)
    : m_tcp_server(tcp_port), m_udp_server(udp_port), m_reactor() {}

void Server::Start()
{
    Logger &logger = *(Singleton<Logger>::Instance());
    int status;

    status = m_udp_server.CreateSocket();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "UDP server: failed to bind\n");
        return;
    }

    status = m_tcp_server.CreateSocket();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "TCP server: failed to bind\n");
        return;
    } 

    status = m_tcp_server.Listen();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "TCP server listen error\n");
    }

    logger.Log(Logger::INFO, "TCP server: waiting for connections...\n");

    m_reactor.AddFD(
        m_tcp_server.GetSocket(),
        Reactor::READ,
        TCPListenerFunction(m_tcp_server.GetSocket(), &m_reactor));
    
    m_reactor.AddFD(
        m_udp_server.GetSocket(),
        Reactor::READ,
        UDPServerReadFunction(m_udp_server.GetSocket(), &m_reactor));
    
    m_reactor.AddFD(
        STDIN_FILENO,
        Reactor::READ,
        ServerConsoleFunction(STDIN_FILENO, &m_reactor));

    m_reactor.Run();
}

ServerConsoleFunction::ServerConsoleFunction(int sockfd_, Reactor *reactor_)
    : m_sockfd(sockfd_), m_reactor(reactor_) {}

void ServerConsoleFunction::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    char str[MAXDATASIZE];

    fgets(str, MAXDATASIZE, stdin);

    if (strcmp(str, "exit\n") == 0)
    {
        logger.Log(Logger::DEBUG, "exit\n");
        logger.Log(Logger::DEBUG, "Exit: Closing all sockets\n");
        CloseAllFD(m_reactor);
        m_reactor->Stop();
        return;
    }
    else if (strcmp(str, "+\n") == 0)
    {
        logger.Log(Logger::DEBUG, "+\n");
        logger.IncOutputSeverity();
    }
    else if (strcmp(str, "-\n") == 0)
    {
        logger.Log(Logger::DEBUG, "-\n");
        logger.DecOutputSeverity();
    }
    else if (strcmp(str, "cout\n") == 0)
    {
        logger.Log(Logger::DEBUG, "SetOutput(std::cout)\n");
        logger.SetOutput(std::cout);
    }

    return;
}

void CloseAllFD(Reactor *reactor)
{
    std::map<FDListener::ModeAndFD, Reactor::Function>::iterator it;
    for (
        it = reactor->GetFDToFuncs()->begin(); 
        it != reactor->GetFDToFuncs()->end();
        ++it)
    {
        close(it->first.first); 
    }
}

UDPServer::UDPServer(int port_)
    : m_port(port_) {}

int UDPServer::CreateSocket()
{
    struct addrinfo *server_ai;

    InitAddrinfo(NULL, m_port, AF_UNSPEC, SOCK_DGRAM, AI_PASSIVE, &server_ai);
    m_sockfd = UDPServerBindSocket(server_ai);
    return m_sockfd;
}

int UDPServer::GetSocket()
{
    return m_sockfd;
}

UDPServerReadFunction::UDPServerReadFunction(int sockfd_, Reactor *reactor_)
    : m_sockfd(sockfd_), m_reactor(reactor_) {}

void UDPServerReadFunction::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    struct addrinfo client_addrinfo;
    socklen_t client_addrlen = sizeof(client_addrinfo);

    char request_buffer[4114];

    recvfrom(m_sockfd, request_buffer, sizeof(request_buffer), MSG_DONTWAIT, (struct sockaddr *)&client_addrinfo, &client_addrlen);

    if ((int)request_buffer[0] == 1) // write request from client
    {
        std::string filename = "block" + lexical_cast<std::string>(*(size_t*)&request_buffer[9]);
        std::ofstream block_file(filename.c_str());

        block_file.write(&request_buffer[17], 4096);

        request_buffer[9] = 1;

        sendto(m_sockfd, request_buffer, 10, MSG_DONTWAIT, (const struct sockaddr *)&client_addrinfo, client_addrlen);
    }
    else if ((int)request_buffer[0] == 0) // read request from client
    {
        std::string filename = "block" + lexical_cast<std::string>(*(size_t*)&request_buffer[9]);
        std::ifstream block_file(filename.c_str());

        request_buffer[9] = 1;
        block_file.read(&request_buffer[10], 4096);


        sendto(m_sockfd, request_buffer, 4106, MSG_DONTWAIT, (const struct sockaddr *)&client_addrinfo, client_addrlen);
    }

    // if (nbytes_rcvd == 0)
    // {
    //     logger.Log(Logger::ERROR, "UDP server recvfrom error: ");
    //     logger.Log(Logger::ERROR, strerror(errno));
    //     logger.Log(Logger::ERROR, "\n");
    //     return;
    // }

    // if (nbytes_rcvd == -1)
    // {
    //     logger.Log(Logger::ERROR, "UDP server recvfrom error: ");
    //     logger.Log(Logger::ERROR, strerror(errno));
    //     logger.Log(Logger::ERROR, "\n");
    //     return;
    // }

    // logger.Log(Logger::DEBUG, "UDP server: received: ");
    // logger.Log(Logger::DEBUG, buff);
    // logger.Log(Logger::DEBUG, "\n");

    // if (strcmp(buff, "Ping") == 0)
    // {
    //     nbytes_sent = sendto(
    //         m_sockfd,
    //         pong_msg,
    //         len_pong_msg,
    //         MSG_CONFIRM,
    //         (const struct sockaddr *)&client_addrinfo,
    //         client_addrlen);

    //     if (nbytes_sent == -1)
    //     {
    //         logger.Log(Logger::ERROR, "UDP server send error\n");
    //     }
    // }
    
    return;
}

TCPServer::TCPServer(int port_)
    : m_port(port_) {}

int TCPServer::CreateSocket()
{
    struct addrinfo *server_ai;
    InitAddrinfo(NULL, m_port, AF_UNSPEC, SOCK_STREAM, AI_PASSIVE, &server_ai);
    m_sockfd = TCPServerBindSocket(server_ai);
    return m_sockfd;
}

int TCPServer::GetSocket()
{
    return m_sockfd;
}

int TCPServer::Listen()
{
    return listen(m_sockfd, m_backlog);
}

TCPListenerFunction::TCPListenerFunction(int sockfd_, Reactor *reactor_)
    : m_sockfd(sockfd_), m_reactor(reactor_) {}

void TCPListenerFunction::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    int new_sockfd;
    struct sockaddr_storage client_ai;
    socklen_t client_addrlen;
    client_addrlen = sizeof(client_addrlen);

    new_sockfd = accept(m_sockfd, (struct sockaddr *)&client_ai, &client_addrlen);

    if (new_sockfd == -1)
    {
        logger.Log(Logger::ERROR, "accept: ");
        logger.Log(Logger::ERROR, strerror(errno));
        logger.Log(Logger::ERROR, "\n");
        return;
    }

    m_reactor->AddFD(
        new_sockfd,
        Reactor::READ,
        TCPServerReadFunction(new_sockfd, m_reactor));
}

TCPServerReadFunction::TCPServerReadFunction(int sockfd_, Reactor *reactor_)
    : m_sockfd(sockfd_), m_reactor(reactor_) {}

void TCPServerReadFunction::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    char buff[MAXDATASIZE];
    ssize_t nbytes_sent, nbytes_rcvd;
    const char *pong_msg = "Pong";
    size_t len_pong_msg = strlen(pong_msg);

    nbytes_rcvd = recv(m_sockfd, buff, MAXDATASIZE, 0);
    if (nbytes_rcvd == 0)
    {
        logger.Log(Logger::DEBUG, "Closing TCP connection\n");
        close(m_sockfd);
        m_reactor->RemoveFD(m_sockfd, Reactor::READ);
        return;
    }

    if (nbytes_rcvd == -1)
    {
        logger.Log(Logger::ERROR, "TCP server recv error: ");
        logger.Log(Logger::ERROR, strerror(errno));
        logger.Log(Logger::ERROR, "\n");
    }

    buff[nbytes_rcvd] = '\0';

    logger.Log(Logger::DEBUG, "TCP server: received: ");
    logger.Log(Logger::DEBUG, buff);
    logger.Log(Logger::DEBUG, "\n");

    if (strcmp(buff, "Ping") == 0)
    {
        nbytes_sent = send(m_sockfd, pong_msg, len_pong_msg, 0);

        if (nbytes_sent == -1)
        {
            logger.Log(Logger::ERROR, "TCP server send error\n");
        }
    }
}

} //namespace ilrd