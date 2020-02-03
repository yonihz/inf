// gd98 tcp_server.cpp ../server-select/socket.cpp ../logger/logger.cpp -I../server-select -I../logger -o tcp_server.out

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

using namespace ilrd;

#define BACKLOG 10
#define MAXDATASIZE 100

#define UNUSED(x) (void)(x)

void ServerRoutine(int sockfd);

int main(int argc, char *argv[])
{  
    if (argc != 2)
    {
        printf("Error: need 1 ports as argument to run\n");
        return 0;
    }

    int status;
    struct addrinfo *server_ai;
    InitAddrinfo(NULL, atoi(argv[1]), AF_UNSPEC, SOCK_STREAM, AI_PASSIVE, &server_ai);

    int sockfd;
    sockfd = TCPServerBindSocket(server_ai);

    if (sockfd == -1)
    {
        fprintf(stderr, "TCP server: failed to bind\n");
        return 0;
    } 

    status = listen(sockfd, BACKLOG);

    if (status == -1)
    {
        fprintf(stderr, "listen error\n");
    }

    struct sockaddr_storage client_ai;
    socklen_t client_addrlen;
    int new_sockfd;
    client_addrlen = sizeof(client_addrlen);
    new_sockfd = accept(sockfd, (struct sockaddr *)&client_ai, &client_addrlen);

    if (new_sockfd == -1)
    {
        perror("accept");
    }

    ServerRoutine(new_sockfd);

    close(sockfd);
    close(new_sockfd);

    return 0;
}

void ServerRoutine(int sockfd)
{
    char buff[MAXDATASIZE];
    const char *msg = "Ping";
    ssize_t nbytes_sent, nbytes_rcvd;
    size_t len_msg;
    const size_t count = 10;
    size_t i = 0;

    len_msg = strlen(msg);

    for (i = 0; i < count; ++i)
    {
        nbytes_rcvd = recv(sockfd, buff, MAXDATASIZE, 0);

        if (nbytes_rcvd == 0)
        {
            printf("client closed connection\n");
            break;
        }

        if (nbytes_rcvd == -1)
        {
            perror("recv error");
        }

        buff[nbytes_rcvd] = '\0';

        printf("server: received '%s'\n", buff);
        sleep(1);

        nbytes_sent = send(sockfd, msg, len_msg, 0);

        if (nbytes_sent == -1)
        {
            fprintf(stderr, "send error\n");
        }
    }
}