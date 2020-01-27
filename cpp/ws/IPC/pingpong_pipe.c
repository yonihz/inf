#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define COUNT 10

void PingSender(int *pipe_read, int *pipe_write)
{
    size_t i = 0;
    char *str = "Ping\n";
    char buff[10];

    for (i = 0; i < COUNT; ++i)
    {
        write(pipe_write[1], str, strlen(str)+1);
        sleep(1);
        read(pipe_read[0], buff, 10);
        printf("%s", buff);
    }
}

void PongSender(int *pipe_read, int *pipe_write)
{
    size_t i = 0;
    char *str = "Pong\n";
    char buff[10];

    for (i = 0; i < COUNT; ++i)
    {
        read(pipe_read[0], buff, 10);
        printf("%s", buff);
        write(pipe_write[1], str, strlen(str)+1);
        sleep(1);
    }
}

int main()
{
    int p1[2], p2[2];
    pid_t pid;

    pipe(p1);
    pipe(p2);
    pid = fork();

    if (pid == 0)
    {
        PingSender(p1, p2);
    }
    else
    {
        PongSender(p2, p1);
    }

    return 0;
    
}