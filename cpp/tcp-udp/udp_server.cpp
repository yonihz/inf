// gd98 udp_server.cpp ../server-select/socket.cpp ../logger/logger.cpp -I../server-select -I../logger -o udp_server.out

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
    const char *msg = "Ping";
    ssize_t nbytes_sent, nbytes_rcvd;
    size_t len_msg;
    const size_t count = 10;
    size_t i = 0;
    struct sockaddr_storage client_ai;
    socklen_t client_addrlen;

    len_msg = strlen(msg);

    for (i = 0; i < count; ++i)
    {
        client_addrlen = sizeof(client_ai);
        nbytes_rcvd = recvfrom(sockfd, buff, MAXDATASIZE, MSG_WAITALL, (struct sockaddr *)&client_ai, &client_addrlen);

        if (nbytes_rcvd == -1)
        {
            perror("recvfrom error");
        }

        buff[nbytes_rcvd] = '\0';

        printf("listener: received '%s'\n", buff);
        sleep(1);

        nbytes_sent = sendto(sockfd, msg, len_msg, MSG_CONFIRM, (const struct sockaddr *)&client_ai, client_addrlen);

        if (nbytes_sent == -1)
        {
            fprintf(stderr, "sendto error\n");
        }
    }

}