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

#define UNUSED(x) (void)(x)

#define MAXDATASIZE 100
#define BACKLOG 100

namespace ilrd
{

void CreateServer(int tcp_port, int udp_port)
{
    std::ofstream ofs;
    ofs.open("server.log", std::ofstream::out | std::ofstream::app);

    g_logger.SetOutput(ofs);
    // g_logger.Log(Logger::WARNING, "WARNING msg\n");
    // g_logger.Log(Logger::INFO, "INFO msg\n");
    // g_logger.Log(Logger::DEBUG, "DEBUG msg\n");
    // g_logger.Log(Logger::ERROR, "ERROR msg\n");

    int status;
    int fdmax, udp_server_sockfd, tcp_server_sockfd, new_sockfd;
    ssize_t nbytes_read;
    fd_set master, tcp_fds, read_fds;
    struct sockaddr_storage client_ai;
    socklen_t client_addrlen;

    g_logger.Log(Logger::ERROR, "tcp port: ");
    g_logger.Log(Logger::ERROR, lexical_cast<std::string>(tcp_port));
    g_logger.Log(Logger::ERROR, "\n");
    g_logger.Log(Logger::ERROR, strerror(errno));
    g_logger.Log(Logger::ERROR, "\n");


    udp_server_sockfd = UDPServerGetSocket(udp_port);

    if (udp_server_sockfd == -1)
    {
        g_logger.Log(Logger::ERROR, "UDP server: failed to bind\n");
        return;
    }

    tcp_server_sockfd = TCPServerGetSocket(tcp_port);

    if (tcp_server_sockfd == -1)
    {
        g_logger.Log(Logger::ERROR, "TCP server: failed to bind\n");
        return;
    } 

    FD_ZERO(&master);
    FD_ZERO(&tcp_fds);
    FD_ZERO(&read_fds);

    FD_SET(udp_server_sockfd, &master);
    FD_SET(tcp_server_sockfd, &master);
    FD_SET(STDIN_FILENO, &master);
    fdmax = (udp_server_sockfd > tcp_server_sockfd) ? udp_server_sockfd : tcp_server_sockfd;

    status = listen(tcp_server_sockfd, BACKLOG);

    if (status == -1)
    {
        g_logger.Log(Logger::ERROR, "TCP server listen error\n");
    }

    g_logger.Log(Logger::INFO, "TCP server: waiting for connections...\n");

    while (status != -2) 
    {
        struct timeval timev;
        timev.tv_sec = 2;
        timev.tv_usec = 500000;

        read_fds = master;
        status = select(fdmax + 1, &read_fds, NULL, NULL, &timev);

        if (status == 0)
        {
            g_logger.Log(Logger::DEBUG, "select timeout reached, retrying...\n");
            continue; 
        } 

        if (status == -1)
        {
            g_logger.Log(Logger::ERROR, "select error: ");
            g_logger.Log(Logger::ERROR, strerror(errno));
            g_logger.Log(Logger::ERROR, "\n");
            return;
        }

        for (int i = 0; i <= fdmax; ++i)
        {
            if (FD_ISSET(i, &read_fds))
            {
                if (i == 0)
                {
                    status = ServerConsole();

                    if (status == -2)
                    {
                        g_logger.Log(Logger::DEBUG, "Exit: Closing all sockets\n");
                        for (int j = 0; j <= fdmax; ++i)
                        {
                            if (FD_ISSET(j, &master))
                            {
                                close(j);
                            }
                            
                            ofs.close();
                            return;
                        } 
                    }
                }
                else if (i == tcp_server_sockfd)
                {
                    client_addrlen = sizeof(client_addrlen);
                    new_sockfd = accept(tcp_server_sockfd, (struct sockaddr *)&client_ai, &client_addrlen);

                    if (new_sockfd == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(new_sockfd, &master);
                        FD_SET(new_sockfd, &tcp_fds);

                        if (new_sockfd > fdmax)
                        {
                            fdmax = new_sockfd;
                        }
                    }
                }
                else if (FD_ISSET(i, &tcp_fds))
                {
                    nbytes_read = TCPServerRead(i);
                    
                    if (nbytes_read == 0)
                    {
                        std::cout << "closing tcp connection." << std::endl;
                        close(i);
                        FD_CLR(i, &master);
                        FD_CLR(i, &tcp_fds);
                    }
                }
                else
                {
                    UDPServerRead(i);
                }
            }
        }
    }
}

int ServerConsole(void)
{
    char str[MAXDATASIZE]; 

    // printf("Server Console - waiting for input:\n");
    fgets(str, MAXDATASIZE, stdin);

    if (strcmp(str, "exit\n") == 0)
    {
        return -2;
    }

    return 0;
}

int UDPServerGetSocket(int port)
{
    struct addrinfo *server_ai;

    InitAddrinfo(NULL, port, AF_UNSPEC, SOCK_DGRAM, AI_PASSIVE, &server_ai);
    return UDPServerBindSocket(server_ai);
}

ssize_t UDPServerRead(int sock_fd)
{
    struct addrinfo client_addrinfo;
    socklen_t client_addrlen;

    char buff[MAXDATASIZE];
    ssize_t nbytes_sent, nbytes_rcvd;
    const char *pong_msg = "Pong";
    size_t len_pong_msg = strlen(pong_msg);

    client_addrlen = sizeof(client_addrinfo);
    nbytes_rcvd = recvfrom(sock_fd, buff, MAXDATASIZE, MSG_WAITALL, (struct sockaddr *)&client_addrinfo, &client_addrlen);

    if (nbytes_rcvd == 0)
    {
        perror("UDP server recvfrom error");
        return nbytes_rcvd;
    }

    if (nbytes_rcvd == -1)
    {
        perror("UDP server recvfrom error");
        return nbytes_rcvd;
    }

    buff[nbytes_rcvd] = '\0';

    printf("UDP server: received '%s'\n", buff);

    if (strcmp(buff, "Ping") == 0)
    {
        nbytes_sent = sendto(sock_fd, pong_msg, len_pong_msg, MSG_CONFIRM, (const struct sockaddr *)&client_addrinfo, client_addrlen);

        if (nbytes_sent == -1)
        {
            fprintf(stderr, "UDP server send error\n");
        }
    }
    
    return nbytes_rcvd;
}

int TCPServerGetSocket(int port)
{
    struct addrinfo *server_ai;
    InitAddrinfo(NULL, port, AF_UNSPEC, SOCK_STREAM, AI_PASSIVE, &server_ai);
    return TCPServerBindSocket(server_ai);
}

ssize_t TCPServerRead(int sock_fd)
{
    char buff[MAXDATASIZE];
    ssize_t nbytes_sent, nbytes_rcvd;
    const char *pong_msg = "Pong";
    size_t len_pong_msg = strlen(pong_msg);

    nbytes_rcvd = recv(sock_fd, buff, MAXDATASIZE, 0);
    if (nbytes_rcvd == 0)
    {
        return nbytes_rcvd;
    }

    if (nbytes_rcvd == -1)
    {
        perror("TCP server recv error");
        return nbytes_rcvd;
    }

    buff[nbytes_rcvd] = '\0';

    printf("TCP server: received '%s'\n", buff);

    if (strcmp(buff, "Ping") == 0)
    {
        nbytes_sent = send(sock_fd, pong_msg, len_pong_msg, 0);

        if (nbytes_sent == -1)
        {
            fprintf(stderr, "TCP server send error\n");
        }
    }

    return nbytes_rcvd;
}

} //namespace ilrd