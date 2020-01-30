#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>     /* sleep */

#define PORT "5555"
#define MSG_SIZE 10

#define UNUSED(x) (void)(x)

int main()
{
    int status;
    int socket_fd;
    struct addrinfo hints;
    struct addrinfo *serv_info, *p;

    char buf[MSG_SIZE];
    ssize_t nbytes_rcvd;
    const size_t count = 10;
    size_t i = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; /* AF_INET (IPv4), AF_INET6 (IPv6), AF_UNSPEC (both) */
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, PORT, &hints, &serv_info);

    if (status != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    }

    for(p = serv_info; p != NULL; p = p->ai_next)
    {
        socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socket_fd == -1)
        {
            perror("listener: socket");
            continue;
        }

        status = bind(socket_fd, p->ai_addr, p->ai_addrlen);

        if (status == -1)
        {
            close(socket_fd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(serv_info);

    for (i = 0; i < count; ++i)
    {
        nbytes_rcvd = recv(socket_fd, buf, MSG_SIZE, 0);

        if (nbytes_rcvd == -1)
        {
            perror("recvfrom error");
        }

        buf[nbytes_rcvd] = '\0';

        printf("listener: received '%s'\n", buf);
    }

    close(socket_fd);

    return 0;
}