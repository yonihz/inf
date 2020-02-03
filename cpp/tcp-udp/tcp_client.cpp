// gd98 tcp_client.cpp ../server-select/socket.cpp ../logger/logger.cpp -I../server-select -I../logger

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "socket.hpp"

#define MAXDATASIZE 100

#define UNUSED(x) (void)(x)

using namespace ilrd;

void ClientRoutine(int sockfd);

int main(int argc, char *argv[])
{  
    if (argc != 2)
    {
        std::cout << "Error: need 1 ports as argument to run" << std::endl;
        return 0;
    }

    struct addrinfo *server_ai;
    InitAddrinfo(NULL, atoi(argv[1]), AF_UNSPEC, SOCK_STREAM, AI_PASSIVE, &server_ai);

    int sockfd;
    sockfd = ClientConnectSocket(server_ai);

    if (sockfd == -1) 
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    ClientRoutine(sockfd);

    close(sockfd);

    return 0;
}

void ClientRoutine(int sockfd)
{
    char buf[MAXDATASIZE];
    char *msg = "Ping";
    ssize_t nbytes_sent, nbytes_rcvd;
    size_t len_msg;
    const size_t count = 10;
    size_t i = 0;

    len_msg = strlen(msg);

    for (i = 0; i < count; ++i)
    {
        nbytes_sent = send(sockfd, msg, len_msg, 0);

        if (nbytes_sent == -1)
        {
            fprintf(stderr, "send error\n");
        }

        nbytes_rcvd = recv(sockfd, buf, MAXDATASIZE, 0);

        if (nbytes_rcvd == -1)
        {
            perror("recv error");
        }

        buf[nbytes_rcvd] = '\0';

        printf("client: received '%s'\n", buf);
        sleep(1);
    }
}