// gd98 udp_client.cpp ../server-select/socket.cpp ../logger/logger.cpp -I../server-select -I../logger -o udp_client.out

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

#define MAXDATASIZE 100

#define UNUSED(x) (void)(x)

using namespace ilrd;

void ClientRoutine(int sockfd);

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
    sockfd = UDPClientGetSocket(server_ai);

    if (sockfd == -1) 
    {
        fprintf(stderr, "UDP client: failed to connect\n");
        return 2;
    }

    ClientRoutine(sockfd);

    return 0;

}

void ClientRoutine(int sockfd)
{
    char buf[MAXDATASIZE];
    const char *msg = "Ping";
    ssize_t nbytes_sent, nbytes_rcvd;
    size_t len_msg;
    const size_t count = 10;
    size_t i = 0;

    len_msg = strlen(msg);

    for (i = 0; i < count; ++i)
    {
        nbytes_sent = sendto(sockfd, msg, len_msg, MSG_CONFIRM, p->ai_addr, p->ai_addrlen);

        if (nbytes_sent == -1)
        {
            fprintf(stderr, "sendto error\n");
        }

        nbytes_rcvd = recvfrom(sockfd, buf, MAXDATASIZE, MSG_WAITALL, p->ai_addr, &p->ai_addrlen);

        if (nbytes_rcvd == -1)
        {
            perror("recvfrom error");
        }

        buf[nbytes_rcvd] = '\0';

        printf("UDP client: received '%s'\n", buf);
        sleep(1);
    }
}