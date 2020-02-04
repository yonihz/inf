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
#include <signal.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <string>
#include <errno.h>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast; 
using boost::bad_lexical_cast;

#include "server.hpp"
#include "logger.hpp"

#define UNUSUED(x) (void)(x)

#define NTHREADS 3
#define MAXDATASIZE 100
#define BACKLOG 100

namespace ilrd
{

Logger g_logger(Logger::WARNING);
std::ofstream ofs1("file1.log");
std::ofstream ofs2("file2.log");

struct ServerInput
{
public:
    ServerInput(int port_)
        : port(port_) {}
    int port;
};

void CreateServer(int tcp_port, int udp_port)
{
    pthread_t console_th, tcp_th, udp_th;

    ServerInput tcp_in(tcp_port);
    ServerInput udp_in(udp_port);
   
    pthread_create(&console_th, NULL, ConsoleThread, NULL);
    pthread_create(&tcp_th, NULL, TCPServerThread, (void*)&tcp_in);
    pthread_create(&udp_th, NULL, UDPServerThread, (void*)&udp_in);

    pthread_join(console_th, NULL);
    pthread_join(tcp_th, NULL);
    pthread_join(udp_th, NULL);
}

void *ConsoleThread(void* arg)
{
    UNUSUED(arg);
    char str[MAXDATASIZE]; 
    while(1)
    {
        g_logger.Log(Logger::DEBUG, "Server Console - waiting for input:\n");
        fgets(str, MAXDATASIZE, stdin);

        if (strcmp(str, "exit\n") == 0)
        {
            exit(1);
        }
        else if (strcmp(str, "+\n") == 0)
        {
            g_logger.IncOutputSeverity();
        }
        else if (strcmp(str, "-\n") == 0)
        {
            g_logger.DecOutputSeverity();
        }
        else if (strcmp(str, "file1\n") == 0)
        {
            g_logger.SetOutput(ofs1);
        }
        else if (strcmp(str, "file2\n") == 0)
        {
            g_logger.SetOutput(ofs2);
        }
        else if (strcmp(str, "cout\n") == 0)
        {
            g_logger.SetOutput(std::cout);
        }
    }
}

void *TCPServerThread(void *server_in)
{
    int status;
    int sockfd, new_sockfd;
    struct addrinfo *server_addrinfo;
    struct sockaddr_storage client_addrinfo;
    socklen_t client_addrlen;
    std::vector<pthread_t*> connection_threads;
    std::vector<int> connection_sockets;

    InitAddrinfo(NULL,
        (static_cast<ServerInput*>(server_in))->port,
        AF_UNSPEC,
        SOCK_STREAM,
        AI_PASSIVE,
        &server_addrinfo);


    sockfd = TCPServerBindSocket(server_addrinfo);

    if (sockfd == -1)
    {
        g_logger.Log(Logger::ERROR, "TCP server: failed to bind\n");
        return NULL;
    }

    status = listen(sockfd, BACKLOG);

    if (status == -1)
    {
        g_logger.Log(Logger::ERROR, "TCP server listen error\n");
    }

    g_logger.Log(Logger::INFO, "TCP server: waiting for connections...\n");

    while (1)
    {
        client_addrlen = sizeof(client_addrlen);
        new_sockfd = accept(sockfd, (struct sockaddr *)&client_addrinfo, &client_addrlen);
        
        if (new_sockfd == -1)
        {
            g_logger.Log(Logger::ERROR, "accept: ");
            g_logger.Log(Logger::ERROR, strerror(errno));
            g_logger.Log(Logger::ERROR, "\n");
            continue;
        }

        connection_sockets.push_back(new_sockfd);
        pthread_t *new_th = (pthread_t*)malloc(sizeof(pthread_t));
        pthread_create(new_th, NULL, TCPConnectionThread, (void*)&(connection_sockets.back()));
        connection_threads.push_back(new_th);
    }

    close(sockfd);
    return 0;
}

void *TCPConnectionThread(void *new_sockfd_voidptr)
{
    int new_sockfd = *(int*)new_sockfd_voidptr;
    char buff[MAXDATASIZE];
    ssize_t nbytes_sent, nbytes_rcvd;
    const char *pong_msg = "Pong";
    size_t len_pong_msg = strlen(pong_msg);

    while(1)
    {
        nbytes_rcvd = recv(new_sockfd, buff, MAXDATASIZE, 0);
        if (nbytes_rcvd == 0)
        {
            break;
        }

        if (nbytes_rcvd == -1)
        {
            g_logger.Log(Logger::ERROR, "TCP server recv error: ");
            g_logger.Log(Logger::ERROR, strerror(errno));
            g_logger.Log(Logger::ERROR, "\n");
            break;
        }

        buff[nbytes_rcvd] = '\0';

        g_logger.Log(Logger::DEBUG, "TCP server: received: ");
        g_logger.Log(Logger::DEBUG, buff);
        g_logger.Log(Logger::DEBUG, "\n");

        if (strcmp(buff, "Ping") == 0)
        {
            nbytes_sent = send(new_sockfd, pong_msg, len_pong_msg, 0);

            if (nbytes_sent == -1)
            {
                g_logger.Log(Logger::ERROR, "TCP server send error\n");
            }
        }
    }

    return NULL;
}

void *UDPServerThread(void *server_in)
{
    int sockfd;
    struct addrinfo *server_addrinfo;

    InitAddrinfo(
        NULL,
        (static_cast<ServerInput*>(server_in))->port,
        AF_UNSPEC,
        SOCK_DGRAM,
        AI_PASSIVE,
        &server_addrinfo);

    sockfd = UDPServerBindSocket(server_addrinfo);

    if (sockfd == -1)
    {
        g_logger.Log(Logger::ERROR, "UDP server: failed to bind\n");
        return NULL;
    }

    g_logger.Log(Logger::INFO, "UDP server: waiting to recvfrom...\n");

    UDPServerLoop(sockfd);

    close(sockfd);

    return NULL;
}

void UDPServerLoop(int sockfd)
{
    struct addrinfo client_addrinfo;
    socklen_t client_addrlen;

    char buff[MAXDATASIZE];
    ssize_t nbytes_sent, nbytes_rcvd;
    const char *pong_msg = "Pong";
    size_t len_pong_msg = strlen(pong_msg);

    while(1)
    {
        client_addrlen = sizeof(client_addrinfo);
        nbytes_rcvd = recvfrom(sockfd, buff, MAXDATASIZE, MSG_WAITALL, (struct sockaddr *)&client_addrinfo, &client_addrlen);

        if (nbytes_rcvd == -1)
        {
            g_logger.Log(Logger::ERROR, "UDP server recvfrom error: ");
            g_logger.Log(Logger::ERROR, strerror(errno));
            g_logger.Log(Logger::ERROR, "\n");
        }

        buff[nbytes_rcvd] = '\0';

        g_logger.Log(Logger::DEBUG, "UDP server: received: ");
        g_logger.Log(Logger::DEBUG, buff);
        g_logger.Log(Logger::DEBUG, "\n");
  
        if (strcmp(buff, "Ping") == 0)
        {
            nbytes_sent = sendto(sockfd, pong_msg, len_pong_msg, MSG_CONFIRM, (const struct sockaddr *)&client_addrinfo, client_addrlen);

            if (nbytes_sent == -1)
            {
                g_logger.Log(Logger::ERROR, "UDP server send error\n");
            }
        }
    }
}

} //namespace ilrd