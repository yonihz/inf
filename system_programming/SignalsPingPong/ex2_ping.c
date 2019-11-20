/* compile command:
gcc -pedantic-errors -Wall -Wextra -g ex2_ping.c -o ex2_ping.out
*/

/* run command:
./ex2_ping.out ~/git/system_programming/SignalsPingPong/ex2_pong.out
*/

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

int main(int argc, char *argv[])
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

    pid = fork();

    UNUSED(argc);

    while (1)
    {
        if (pid == 0) /* child */
        {
            execl(argv[1], argv[2], (char*)NULL);
        }
        else if (pid > 0) /* parent */
        {
            kill(pid, SIGUSR2);
            pause();
            sleep(1);
        }
        else
        {
            printf("Fork failed\n");
        }
    }
        return (0);                                                                                                                                                        
}