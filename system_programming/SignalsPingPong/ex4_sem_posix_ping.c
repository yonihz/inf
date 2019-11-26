/* compile command:
gd ex4_ping.c -pthread
*/

/* list named semaphores:
ls -al /dev/shm/sem.*
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>           /* O_* constants */
#include <sys/stat.h>        /* mode constants */
#include <semaphore.h>

#define UNUSED(x) (void)(x)

#define SEM1_NAME "/sem1"
#define SEM2_NAME "/sem2"

sem_t *sem1, *sem2;

int main()
{
    sem_unlink(SEM1_NAME);
    sem_unlink(SEM2_NAME);
    sem1 = sem_open(SEM1_NAME, O_CREAT, 0660, 1);
    sem2 = sem_open(SEM2_NAME, O_CREAT, 0660, 0);
    
    if (SEM_FAILED == sem1 || SEM_FAILED == sem2)
    {
        return (0);
    }

    while (1)
    {
        sem_wait(sem1);
        sleep(1);
        printf("Ping\n");
        sem_post(sem2);
    }

    return (0);                                                                                                                                                        
}