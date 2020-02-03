// gd98 udp_server_bc.cpp ../server-select/socket.cpp ../logger/logger.cpp -I../server-select -I../logger -o udp_server_bc.out

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

    struct addrinfo *server_ai;
    InitAddrinfo(NULL, atoi(argv[1]), AF_UNSPEC, SOCK_DGRAM, AI_PASSIVE, &server_ai);

    int sockfd;
    sockfd = UDPServerBindSocket(server_ai);

    ServerRoutine(sockfd);

    close(sockfd);

    return 0;
}

void ServerRoutine(int sockfd)
{
    char buff[MAXDATASIZE];
    ssize_t nbytes_rcvd;
    const size_t count = 10;
    size_t i = 0;

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
            perror("recvfrom error");
        }

        buff[nbytes_rcvd] = '\0';

        printf("listener: received '%s'\n", buff);
    }
}