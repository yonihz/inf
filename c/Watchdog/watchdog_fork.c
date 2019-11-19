#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;

    UNUSED(argc);

    while (1)
    {
        pid = fork();

        if (pid == 0) 
        {
            printf("child\n");
            execv("/usr/bin/gedit", (char* const*)argv[0]);
            sleep(1000);
        }
        else if (pid > 0)
        {
            printf("parent\n");
            pid = wait(&status);

            if (WIFEXITED(status))
            {
                printf("Parent: Child exited with status: %d\n", WEXITSTATUS(status));
            }
        }
        else
        {
            printf("Fork failed\n");
        }
    }
        return (0);                                                                                                                                                        
}