// gd98 tcp_client.cpp ../server-select/socket.cpp ../thread/thread.cpp ../logger/logger.cpp -I../thread/ -I../server-select -I../logger -I../waitable_queue/ -pthread -o tcp_client.out

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
    InitAddrinfo(NULL, atoi(argv[1]), AF_UNSPEC, SOCK_STREAM, AI_PASSIVE, &server_ai);

    int sockfd;
    sockfd = TCPClientConnectSocket(server_ai);

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
    char buff[MAXDATASIZE];
    const char *msg = "Ping";
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

        nbytes_rcvd = recv(sockfd, buff, MAXDATASIZE, 0);

        if (nbytes_rcvd == -1)
        {
            perror("recv error");
        }

        buff[nbytes_rcvd] = '\0';

        printf("client: received '%s'\n", buff);
        sleep(1);
    }
}