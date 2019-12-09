#include <stdio.h> /* printf */
#include <stdlib.h> /* NULL */
#include <unistd.h> /* sleep */
#include <pthread.h>

#include <fcntl.h>           /* O_* constants */
#include <sys/stat.h>        /* mode constants */
#include <semaphore.h>

#define UNUSED(x) (void)(x)

#define SEM1_NAME "/sem1"
#define SEM2_NAME "/sem2"

sem_t *sem1, *sem2;

void *PrintPing(void *a);
void *PrintPong(void *a);

int main()
{
    pthread_t t1, t2;

    t1 = pthread_create(&t1, NULL, PrintPing, NULL);
    t2 = pthread_create(&t1, NULL, PrintPong, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return (0);
}

void *PrintPing(void *a)
{
    sem_unlink(SEM1_NAME);
    sem_unlink(SEM2_NAME);
    sem1 = sem_open(SEM1_NAME, O_CREAT, 0660, 1);
    sem2 = sem_open(SEM2_NAME, O_CREAT, 0660, 0);
    
    UNUSED(a);

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

    return (NULL);                                                                                                                                                        
}

void *PrintPong(void *a)
{
    sem1 = sem_open(SEM1_NAME, O_CREAT, 0660, 1);
    sem2 = sem_open(SEM2_NAME, O_CREAT, 0660, 0);

    UNUSED(a);

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

    return (NULL);                                                                                                                                                      
}