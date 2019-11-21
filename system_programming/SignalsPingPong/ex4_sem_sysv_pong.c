#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x) (void)(x)


int main()
{
    if (SEM_FAILED == sem1 || SEM_FAILED == sem2)
    {
        return (0);
    }

    while (1)
    {
        sem_wait(sem2);
        sleep(1);
        printf("Pong\n");
        sem_post(sem1);
    }

    return (0);                                                                                                                                                        
}