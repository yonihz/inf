#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> /* kill */

#define UNUSED(x) (void)(x)

sig_atomic_t is_waiting = 0;

void sig_handler1(int sig)
{
    UNUSED(sig);
    write(0, "Ping\n", 5);
    is_waiting = 0;
}

int main()
{
    pid_t pid;
    struct sigaction sa1, sa_ignore;

    sa1.sa_handler = &sig_handler1;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGUSR2, &sa_ignore, NULL);
    
    is_waiting = 1;
    
    while (1)
    {
        while(is_waiting);
        is_waiting = 1;
        printf("Enter PID of Pong process:\n");
        scanf("%d", &pid);
        kill(pid, SIGUSR2);
    }

    return (0);                                                                                                                                                        
}