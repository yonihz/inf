/* #include <sys/types.h>  */
/* #include <sys/socket.h> */
/* #include <arpa/inet.h>  */
#include <netinet/in.h> /* socket */
#include <stdio.h>      /* printf */
#include <string.h>     /* memset */
#include <unistd.h>     /* sleep */

#define UNUSED(x) (void)(x)

#define PORT 1234
#define BUFF_SIZE 10
#define PING_COUNT 10

int main()
{
    int socket_fd;
    char buff[BUFF_SIZE];
    char *ping_str = "Pong";
    const size_t count = PING_COUNT;
    size_t i = 0;
    size_t nbytes_rcv;
    socklen_t len;

    struct sockaddr_in server_addr, client_addr;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_addr, 0 , sizeof(server_addr));
    memset(&client_addr, 0 , sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(socket_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    for (i = 0; i < count; ++i)
    {
        nbytes_rcv = recvfrom(
            socket_fd,
            (char *)buff,
            sizeof(buff),
            MSG_WAITALL,
            (struct sockaddr*)&client_addr,
            &len);
    
        UNUSED(nbytes_rcv);
        printf("%s\n", buff);
        sleep(1);

        sendto(
            socket_fd,
            (const char *)ping_str,
            sizeof(ping_str),
            MSG_CONFIRM,
            (const struct sockaddr*)&client_addr,
            sizeof(client_addr));
    }

    close(socket_fd);
    
    return 0;
}