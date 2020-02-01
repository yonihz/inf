#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>     /* sleep */

#define PORT "1235"
#define MSG_SIZE 10

#define UNUSED(x) (void)(x)

int main()
{
    int status;
    int socket_fd;
    struct addrinfo hints, *serv_info, *p;

    char buf[MSG_SIZE];
    char *msg = "Pong";
    ssize_t nbytes_sent, nbytes_rcvd;
    size_t len_msg;
    const size_t count = 10;
    size_t i = 0;

    len_msg = strlen(msg);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; /* AF_INET (IPv4), AF_INET6 (IPv6), AF_UNSPEC (both) */
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, PORT, &hints, &serv_info);
    if (status != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    }

    for (p = serv_info; p != NULL; p = p->ai_next)
    {
        socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socket_fd == -1)
        {
            perror("talker: socket");
            continue;
        }

        break;
    }

    if (p == NULL) 
    {
        fprintf(stderr, "talker: failed to connect\n");
        return 2;
    }

    freeaddrinfo(serv_info);

    for (i = 0; i < count; ++i)
    {
        nbytes_sent = sendto(socket_fd, msg, len_msg, MSG_CONFIRM, p->ai_addr, p->ai_addrlen);

        if (nbytes_sent == -1)
        {
            fprintf(stderr, "sendto error\n");
        }

        nbytes_rcvd = recvfrom(socket_fd, buf, MSG_SIZE, MSG_WAITALL, p->ai_addr, &p->ai_addrlen);

        if (nbytes_rcvd == -1)
        {
            perror("recvfrom error");
        }

        buf[nbytes_rcvd] = '\0';

        printf("talker: received '%s'\n", buf);
        sleep(1);
    }

    return 0;

}