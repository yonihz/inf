#include <stdio.h> /* printf */
#include <stdlib.h> /* NULL */
#include <unistd.h> /* sleep */
#include <pthread.h>

#include <fcntl.h>           /* O_* constants */
#include <sys/stat.h>        /* mode constants */
#include <semaphore.h>

#define UNUSED(x) (void)(x)

sem_t sem1, sem2;

void *PrintPing(void *a);
void *PrintPong(void *a);

int main()
{
    pthread_t t1, t2;

    sem_init(&sem1, 0, 1);
    sem_init(&sem1, 0, 0);
    t1 = pthread_create(&t1, NULL, PrintPing, NULL);
    t2 = pthread_create(&t1, NULL, PrintPong, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return (0);
}

void *PrintPing(void *a)
{
    UNUSED(a);

    while (1)
    {
        sem_wait(&sem1);
        sleep(1);
        printf("Ping\n");
        sem_post(&sem2);
    }

    return (NULL);                                                                                                                                                        
}

void *PrintPong(void *a)
{

    UNUSED(a);

    while (1)
    {
        sem_wait(&sem2);
        sleep(1);
        printf("Pong\n");
        sem_post(&sem1);
    }

    return (NULL);                                                                                                                                                      
}