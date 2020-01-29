/* gd tcp_server.c -D_POSIX_C_SOURCE=200112L -o tcp_server.out */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>     /* sleep */

#define PORT "1234"
#define BACKLOG 10
#define MSG_SIZE 10

#define UNUSED(x) (void)(x)

int main()
{
    int status;
    int socket_fd, new_socket_fd;
    struct addrinfo hints;
    struct addrinfo *serv_info, *p;
    struct addrinfo other_addr;
    socklen_t addr_size;

    char buf[MSG_SIZE];
    char *msg = "Ping";
    ssize_t nbytes_sent, nbytes_rcvd;
    size_t len_msg;
    const size_t count = 10;
    size_t i = 0;

    len_msg = strlen(msg);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; /* AF_INET (IPv4), AF_INET6 (IPv6), AF_UNSPEC (both) */
    hints.ai_socktype = SOCK_STREAM;
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
            perror("server: socket");
            continue;
        }

        /*
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }
        */

        status = bind(socket_fd, p->ai_addr, p->ai_addrlen);

        if (status == -1)
        {
            close(socket_fd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(serv_info);

    status = listen(socket_fd, BACKLOG);

    if (status == -1)
    {
        fprintf(stderr, "listen error\n");
    }

    /*
    while(1) // loop so it can be used to to accept multiple connections and fork()
    {
        if (fork() =! 0)
        {
            close(socket_fd); // child doesn't need the listener
            if (send(new_socket_fd, "Hello, world!", 13, 0) == -1)
            {
                perror("send");
            }
            close(new_socket_fd);
            exit(0);
        }
    }
    */

    addr_size = sizeof(other_addr);
    new_socket_fd = accept(socket_fd, (struct sockaddr *)&other_addr, &addr_size);
    if (new_socket_fd == -1)
    {
        perror("accept");
    }

    for (i = 0; i < count; ++i)
    {
        nbytes_rcvd = recv(new_socket_fd, buf, MSG_SIZE, 0);

        if (nbytes_rcvd == -1)
        {
            perror("recv error");
        }

        buf[nbytes_rcvd] = '\0';

        printf("client: received '%s'\n", buf);
        sleep(1);

        nbytes_sent = send(new_socket_fd, msg, len_msg, 0);

        if (nbytes_sent == -1)
        {
            fprintf(stderr, "send error\n");
        }
    }

    close(socket_fd);
    close(new_socket_fd);

    return 0;
}