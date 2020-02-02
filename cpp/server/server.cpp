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

#include "server.hpp"

using namespace ilrd;

#define UNUSUED(x) (void)(x)

#define NTHREADS 3
#define MAXDATASIZE 100
#define BACKLOG 100

struct ServerInput
{
public:
    ServerInput(const char *ip_, const char *port_, Logger *logger_)
        : ip(ip_), port(port_), logger(logger_) {}
    const char *ip;
    const char *port;
    Logger *logger;
};

void CreateServer(const char *tcp_port, const char *udp_port, const char *bc_port)
{
    std::ofstream ofs;
    ofs.open("server.log", std::ofstream::out | std::ofstream::app);

    Logger logger(Logger::WARNING);
    logger.SetOutput(ofs);
    pthread_t console_th, tcp_th, udp_th, bc_th;

    ServerInput tcp_in(NULL, tcp_port, &logger);
    ServerInput udp_in(NULL, udp_port, &logger);
    ServerInput bc_in(NULL, bc_port, &logger);
   
    pthread_create(&console_th, NULL, ConsoleThread, NULL);
    pthread_create(&tcp_th, NULL, TCPServerThread, (void*)&tcp_in);
    pthread_create(&udp_th, NULL, UDPServerThread, (void*)&udp_in);
    pthread_create(&bc_th, NULL, UDPBroadcastServerThread, (void*)&bc_in);

    pthread_join(console_th, NULL);
    pthread_join(tcp_th, NULL);
    pthread_join(udp_th, NULL);
    pthread_join(bc_th, NULL);
}

void *ConsoleThread(void* arg)
{
    UNUSUED(arg);
    char str[MAXDATASIZE]; 
    while(1)
    {
        printf("Server Console - waiting for input:\n");
        fgets(str, MAXDATASIZE, stdin);

        if (strcmp(str, "exit") == 0)
        {
            //pthread_kill(thread, signo);
        }
    }
}

void *TCPServerThread(void *server_in)
{
    int status;
    int socket_fd, new_socket_fd;
    struct addrinfo *server_addrinfo;
    struct sockaddr_storage client_addrinfo;
    socklen_t client_addrlen;
    pid_t pid;

    printf("TCPServerThread started\n");

    InitAddrinfo(
        NULL,
        "5555",
        AF_UNSPEC,
        SOCK_STREAM,
        AI_PASSIVE,
        &server_addrinfo); // fix args


    socket_fd = TCPServerBindSocket(server_addrinfo);

    if (socket_fd == -1)
    {
        fprintf(stderr, "TCP server: failed to bind\n");
        exit(1);
    }

    status = listen(socket_fd, BACKLOG); // backlog - user defined?

    if (status == -1)
    {
        fprintf(stderr, "TCP server listen error\n");
    }

    printf("TCP server: waiting for connections...\n");

    while (1)
    {
        client_addrlen = sizeof(client_addrlen);
        new_socket_fd = accept(socket_fd, (struct sockaddr *)&client_addrinfo, &client_addrlen);
        
        if (new_socket_fd == -1)
        {
            perror("TCP server: accept");
            continue;
        }

        PrintClientAddr(&client_addrinfo);
        
        pid = fork();
        if (pid == 0)   /* child process */
        { 
            close(socket_fd);
            TCPServerLoop(new_socket_fd);
        }
        else    /* parent process */
        {
            close(new_socket_fd);
        }
    }

    close(socket_fd);
    return 0;
}

void TCPServerLoop(int new_socket_fd)
{
    char buff[MAXDATASIZE];
    ssize_t nbytes_sent, nbytes_rcvd;
    const char *pong_msg = "Pong";
    size_t len_pong_msg = strlen(pong_msg);

    while(1)
    {
        nbytes_rcvd = recv(new_socket_fd, buff, MAXDATASIZE, 0);

        if (nbytes_rcvd == -1)
        {
            perror("TCP server recv error");
        }

        buff[nbytes_rcvd] = '\0';

        printf("TCP server: received '%s'\n", buff);

        if (strcmp(buff, "Ping") == 0)
        {
            nbytes_sent = send(new_socket_fd, pong_msg, len_pong_msg, 0);

            if (nbytes_sent == -1)
            {
                fprintf(stderr, "TCP server send error\n");
            }
        }
    }
}

void *UDPServerThread(void *server_in)
{
    int socket_fd;
    struct addrinfo *server_addrinfo;

    InitAddrinfo(
        NULL,
        "5556",
        AF_UNSPEC,
        SOCK_DGRAM,
        AI_PASSIVE,
        &server_addrinfo); // fix args

    socket_fd = UDPServerBindSocket(server_addrinfo);

    if (socket_fd == -1)
    {
        fprintf(stderr, "UDP server: failed to bind\n");
        exit(1);
    }

    printf("UDP server: waiting to recvfrom...\n");

    UDPServerLoop(socket_fd);

    close(socket_fd);

    return NULL;
}

void UDPServerLoop(int socket_fd)
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
        nbytes_rcvd = recvfrom(socket_fd, buff, MAXDATASIZE, MSG_WAITALL, (struct sockaddr *)&client_addrinfo, &client_addrlen);

        if (nbytes_rcvd == -1)
        {
            perror("UDP server recvfrom error");
        }

        buff[nbytes_rcvd] = '\0';

        printf("UDP server: received '%s'\n", buff);
  
        if (strcmp(buff, "Ping") == 0)
        {
            nbytes_sent = sendto(socket_fd, pong_msg, len_pong_msg, MSG_CONFIRM, (const struct sockaddr *)&client_addrinfo, client_addrlen);

            if (nbytes_sent == -1)
            {
                fprintf(stderr, "UDP server send error\n");
            }
        }
    }
}

void *UDPBroadcastServerThread(void *server_in)
{
    int socket_fd;
    struct addrinfo *server_addrinfo;

    InitAddrinfo(
        NULL,
        "5557",
        AF_UNSPEC,
        SOCK_DGRAM,
        AI_PASSIVE,
        &server_addrinfo); // fix args

    socket_fd = UDPServerBindSocket(server_addrinfo);

    if (socket_fd == -1)
    {
        fprintf(stderr, "UDP server: failed to bind\n");
        exit(1);
    }

    printf("UDP Broadcast server: waiting to recv...\n");

    UDPBroadcastServerLoop(socket_fd);

    close(socket_fd);

    return NULL;
}

void UDPBroadcastServerLoop(int socket_fd)
{
    char buff[MAXDATASIZE];
    ssize_t nbytes_rcvd;

    while(1)
    {
        nbytes_rcvd = recv(socket_fd, buff, MAXDATASIZE, 0);

        if (nbytes_rcvd == -1)
        {
            perror("UDP BC server recvfrom error");
        }

        buff[nbytes_rcvd] = '\0';

        printf("UDP BC server: received '%s'\n", buff);
    }
}