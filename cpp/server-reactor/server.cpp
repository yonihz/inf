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

ConsoleListener::ConsoleListener(int sockfd_, Reactor *reactor_)
    : m_sockfd(sockfd_), m_reactor(reactor_) {}

void ConsoleListener::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    char str[MAXDATASIZE];

    fgets(str, MAXDATASIZE, stdin);
    logger.Log(Logger::DEBUG, std::string(str));

    if (strcmp(str, "exit\n") == 0)
    {
        logger.Log(Logger::DEBUG, "Exit: Closing all sockets\n");
        m_reactor->Stop();
        return;
    }
    else if (strcmp(str, "+\n") == 0)
    {
        logger.IncOutputSeverity();
    }
    else if (strcmp(str, "-\n") == 0)
    {
        logger.DecOutputSeverity();
    }
    else if (strcmp(str, "cout\n") == 0)
    {
        logger.Log(Logger::DEBUG, "SetOutput(std::cout)\n");
        logger.SetOutput(std::cout);
    }

    return;
}

UDPListener::UDPListener(int port_, Reactor *reactor_)
    : m_port(port_), m_reactor(reactor_) {}

void UDPListener::CloseSocket()
{
    close(m_sockfd);
}


int UDPListener::CreateSocket()
{
    struct addrinfo *server_ai;

    InitAddrinfo(NULL, m_port, AF_UNSPEC, SOCK_DGRAM, AI_PASSIVE, &server_ai);
    m_sockfd = UDPServerBindSocket(server_ai);
    return m_sockfd;
}

int UDPListener::GetSocket()
{
    return m_sockfd;
}

UDPProcessRequest::UDPProcessRequest(int sockfd_, Reactor *reactor_)
    : m_sockfd(sockfd_), m_reactor(reactor_) {}

void UDPProcessRequest::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    struct addrinfo client_addrinfo;
    socklen_t client_addrlen;

    char buff[MAXDATASIZE];
    ssize_t nbytes_sent, nbytes_rcvd;
    const char *pong_msg = "Pong";
    size_t len_pong_msg = strlen(pong_msg);

    client_addrlen = sizeof(client_addrinfo);
    nbytes_rcvd = recvfrom(
        m_sockfd,
        buff,
        MAXDATASIZE,
        MSG_WAITALL,
        (struct sockaddr *)&client_addrinfo,
        &client_addrlen);

    if (nbytes_rcvd == 0)
    {
        logger.Log(Logger::ERROR, "UDP server recvfrom error: " + std::string(strerror(errno)) + "\n");
        return;
    }

    if (nbytes_rcvd == -1)
    {
        logger.Log(Logger::ERROR, "UDP server recvfrom error: " + std::string(strerror(errno)) + "\n");
        return;
    }

    buff[nbytes_rcvd] = '\0';

    logger.Log(Logger::DEBUG, "UDP server: received: " + std::string(buff) + "\n");

    if (strcmp(buff, "Ping") == 0)
    {
        nbytes_sent = sendto(
            m_sockfd,
            pong_msg,
            len_pong_msg,
            MSG_CONFIRM,
            (const struct sockaddr *)&client_addrinfo,
            client_addrlen);

        if (nbytes_sent == -1)
        {
            logger.Log(Logger::ERROR, "UDP server send error\n");
        }
    }
    
    return;
}

TCPListener::TCPListener(int port_, Reactor *reactor_)
    : m_port(port_), m_sockfd() , m_connections(), m_reactor(reactor_) {}

void TCPListener::CloseSocket()
{
    close(m_sockfd);
}

void TCPListener::CloseAllConnections()
{
    std::set<int>::iterator it;
    std::set<int>::iterator it_end = m_connections->end();
    for (it = m_connections->begin(); it != it_end; ++it)
    {
        close(*it);
    }
}

void TCPListener::CloseConnection(int sockfd)
{
    m_connections->erase(sockfd);
    close(sockfd);
}

int TCPListener::CreateSocket()
{
    struct addrinfo *server_ai;
    InitAddrinfo(NULL, m_port, AF_UNSPEC, SOCK_STREAM, AI_PASSIVE, &server_ai);
    m_sockfd = TCPServerBindSocket(server_ai);
    return m_sockfd;
}

int TCPListener::GetSocket()
{
    return m_sockfd;
}

int TCPListener::Listen()
{
    return listen(m_sockfd, backlog);
}

void TCPListener::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    int new_sockfd;
    struct sockaddr_storage client_ai;
    socklen_t client_addrlen;
    client_addrlen = sizeof(client_addrlen);

    new_sockfd = accept(m_sockfd, (struct sockaddr *)&client_ai, &client_addrlen);

    if (new_sockfd == -1)
    {
        logger.Log(Logger::ERROR, "accept: " + std::string(strerror(errno)) + "\n");
        return;
    }

    m_connections->insert(new_sockfd);

    m_reactor->AddFD(
        new_sockfd,
        Reactor::READ,
        TCPProcessRequest(new_sockfd, m_reactor, this));
}

TCPProcessRequest::TCPProcessRequest(int sockfd_, Reactor *reactor_, TCPListener *tcp_listener_)
    : m_sockfd(sockfd_), m_reactor(reactor_), m_tcp_listener(tcp_listener_) {}

void TCPProcessRequest::operator()(void)
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
        m_tcp_listener->CloseConnection(m_sockfd);
        m_reactor->RemoveFD(m_sockfd, Reactor::READ);
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
        nbytes_sent = send(m_sockfd, pong_msg, len_pong_msg, 0);

        if (nbytes_sent == -1)
        {
            logger.Log(Logger::ERROR, "TCP server send error\n");
        }
    }
}

} //namespace ilrd