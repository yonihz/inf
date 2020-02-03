#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#include "socket.hpp"
// #include "logger.hpp"

namespace ilrd
{

void InitAddrinfo(const char *ip, const char *port, int ai_family, int ai_socktype, int ai_flags, struct addrinfo **server_addrinfo)
{
    int status;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = ai_family; /* AF_INET (IPv4), AF_INET6 (IPv6), AF_UNSPEC (both) */
    hints.ai_socktype = ai_socktype; /* SOCK_STREAM, SOCK_DGRAM */
    hints.ai_flags = ai_flags; /* AI_PASSIVE */

    status = getaddrinfo(ip, port, &hints, server_addrinfo);

    if (status != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        //return 1;
    }
}

/* frees serv_info, returns -1 or error */
int TCPServerBindSocket(struct addrinfo *serv_info)
{
    struct addrinfo *p = NULL;
    int socket_fd = 0;
    int status = 0, yes = 1;

    for (p = serv_info; p != NULL; p = p->ai_next)
    {
        socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socket_fd == -1)
        {
            perror("server: socket");
            continue;
        }

        status = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (status == -1)
        {
            perror("server: setsockopt");
            continue;
        }
        
        status = bind(socket_fd, p->ai_addr, p->ai_addrlen);
        if (status == -1)
        {
            close(socket_fd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL) 
    {
        return (-1);
    }

    freeaddrinfo(serv_info);

    return socket_fd;
}

/* frees serv_info, returns -1 or error */
int ClientConnectSocket(struct addrinfo *server_addrinfo)
{
    struct addrinfo *p = NULL;
    int socket_fd = 0;
    int status = 0;

    for (p = server_addrinfo; p != NULL; p = p->ai_next)
    {
        socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socket_fd == -1)
        {
            perror("client: socket");
            continue;
        }

        status = connect(socket_fd, p->ai_addr, p->ai_addrlen);
        if (status == -1) 
        {
            close(socket_fd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) 
    {
        fprintf(stderr, "client: failed to connect\n");
    }

    freeaddrinfo(server_addrinfo);

    return socket_fd;
}

/* frees serv_info, returns -1 or error */
int UDPServerBindSocket(struct addrinfo *server_addrinfo)
{
    struct addrinfo *p = NULL;
    int socket_fd = 0;
    int status = 0;

    for (p = server_addrinfo; p != NULL; p = p->ai_next)
    {
        socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socket_fd == -1)
        {
            perror("UDP server: socket");
            continue;
        }

        status = bind(socket_fd, p->ai_addr, p->ai_addrlen);

        if (status == -1)
        {
            close(socket_fd);
            perror("UDP server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(server_addrinfo);

    if (p == NULL)
    {
        fprintf(stderr, "UDP server: failed to bind socket\n");
        return -1;
    }

    return socket_fd;
}

void PrintClientAddr(struct sockaddr_storage *client_addrinfo)
{
    char s[INET6_ADDRSTRLEN];
    struct sockaddr *sa = (struct sockaddr *)client_addrinfo;
    void *src;

    if (sa->sa_family == AF_INET) {
        src = &(((struct sockaddr_in*)sa)->sin_addr);
    }
    else
    {
        src = &(((struct sockaddr_in6*)sa)->sin6_addr);
    }

    inet_ntop(client_addrinfo->ss_family, src, s, sizeof s);
    printf("server: got connection from %s\n", s);
}

}