#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

#define UNUSED(x) (void)(x)

/* run command:
./a.out /usr/bin/gedit
*/

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
            printf("%s: fork_pid = %d\n", argv[1], pid);
            printf("%s: ppid = %d\n", argv[1], getppid());
            printf("%s: pid = %d\n", argv[1], getpid());
            execl(argv[1], (argv[2]));
        }
        else if (pid > 0)
        {
            printf("Watchdog: fork_pid = %d\n", pid);
            printf("Watchdog: ppid = %d\n", getppid());
            printf("Watchdog: pid = %d\n", getpid());
            pid = wait(&status);
            printf("Watchdog: wait_pid = %d\n", pid);
            if (WIFEXITED(status))
            {
                printf("Child exit status: %d\n", WEXITSTATUS(status));
            }
        }
        else
        {
            printf("Fork failed\n");
        }
    }
        return (0);                                                                                                                                                        
}