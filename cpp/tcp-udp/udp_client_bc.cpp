// gd98 udp_client_bc.cpp ../server-select/socket.cpp ../logger/logger.cpp -I../server-select -I../logger -o udp_client_bc.out

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

int main(int argc, char *argv[])
{  
    if (argc != 2)
    {
        printf("Error: need 1 ports as argument to run\n");
        return 0;
    }

    int status;
    int socket_fd;
    struct sockaddr_in other_addr;
    struct hostent *host;
    int nbytes_sent;
    int broadcast = 1; /* char broadcast = '1'; */
    const char *msg = "Hello";

    host = gethostbyname("255.255.255.255");

    if (host == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (socket_fd == -1) 
    {
        perror("socket");
        exit(1);
    }

    status = setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
    if (status == -1)
    {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }

    other_addr.sin_family = AF_INET;
    other_addr.sin_port = htons(atoi(argv[1]));
    other_addr.sin_addr = *((struct in_addr *)host->h_addr_list[0]);
    memset(other_addr.sin_zero, '\0', sizeof other_addr.sin_zero);

    nbytes_sent = sendto(socket_fd, msg, strlen(msg), 0, (struct sockaddr *)&other_addr, sizeof other_addr);

    if (nbytes_sent == -1)
    {
        perror("sendto");
        exit(1);
    }

    printf("sent %d bytes to %s\n", nbytes_sent, inet_ntoa(other_addr.sin_addr));

    close(socket_fd);

    return 0;
}