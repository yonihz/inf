/* compile command:
gcc -pedantic-errors -Wall -Wextra -g ex2_pong.c -o ex2_pong.out
*/

/* run command:
(exectued by ex2_ping)
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> /* kill */

#define UNUSED(x) (void)(x)

void sig_handler2(int sig)
{
    UNUSED(sig);
    write(0, "Pong\n", 5);
}

int main(int argc, char *argv[])
{
    struct sigaction sa2, sa_ignore;

    sa2.sa_handler = &sig_handler2;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, NULL);

    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGUSR1, &sa_ignore, NULL);

    UNUSED(argc);
    UNUSED(argv);

    while (1)
    {
        kill(getppid(), SIGUSR1);
        pause();
        sleep(1);
    }
    
    return (0);                                                                                                                                                        
}