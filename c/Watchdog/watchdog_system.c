#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define UNUSED(x) (void)(x)

/* run command:
./a.out /usr/bin/gedit
*/

int main(int argc, char *argv[])
{
    UNUSED(argc);

    while (1)
    {
        int ret = 0;

        ret = system(argv[1]);

       if (WIFSIGNALED(ret) &&
           (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT))
        {
            break;
        }
    }
    return (0);                                                                                                                                                        
}