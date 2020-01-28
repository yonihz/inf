#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/stat.h>

#define COUNT 10

int main()
{
    int fd1, fd2;
    char *fifo_path1 = "fifo1";
    char *fifo_path2 = "fifo2";
    size_t i = 0;
    char *str = "Pong\n";
    char buff[10];

    mkfifo(fifo_path1, 0666);
    mkfifo(fifo_path2, 0666);

    for (i = 0; i < COUNT; ++i)
    {
        fd1 = open(fifo_path1, O_RDONLY);
        fd2 = open(fifo_path2, O_WRONLY);
        read(fd1, buff, 10);
        printf("%s", buff);
        sleep(1);
        write(fd2, str, strlen(str)+1);
    }
    
    return 0;
}