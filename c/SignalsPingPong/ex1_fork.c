#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> /* kill */

#define UNUSED(x) (void)(x)

void sig_handler1(int sig)
{
    UNUSED(sig);
    write(0, "Ping\n", 5);
}

void sig_handler2(int sig)
{
    UNUSED(sig);    
    write(0, "Pong\n", 5);
}

int main()
{
    pid_t pid;
    struct sigaction sa1, sa2;

    sa1.sa_handler = &sig_handler1;
    sa2.sa_handler = &sig_handler2;
    sigemptyset(&sa1.sa_mask);
    sigemptyset(&sa2.sa_mask);
    sa1.sa_flags = 0;
    sa2.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);
    sigaction(SIGUSR2, &sa2, NULL);

    pid = fork();

    while(1)
    {
        if (pid == 0) /* child */
        {
            kill(getppid(), SIGUSR2);
            pause();
            sleep(1);
        }
        else if (pid > 0) /* parent */
        {
            kill(pid, SIGUSR1);
            pause();
            sleep(1);
        }
        else
        {
            printf("Fork failed\n");
        }
    }                                                                                                                                                 
}