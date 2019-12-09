#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>

#include "queue.h"

#define SIZE 40
#define NCONS 4
#define NPROD 4

pthread_mutex_t lock;
sem_t sem;
size_t counter = 0;
size_t prod_id = 1, cons_id = 1;

void *producer(void *queue_void);
void *consumer(void *queue_void);

int main()
{
    pthread_t prod[NPROD];
    pthread_t cons[NCONS];
    size_t i = 0;

    queue_t *queue = NULL;

    queue = QCreate();
    pthread_mutex_init(&lock, NULL);
    sem_init(&sem, 0, 0);

    for (i = 0; i < NPROD; i++)
    {
        pthread_create(&(prod[i]), NULL, &producer, queue);
    }

    for (i = 0; i < NCONS; i++)
    {
        pthread_create(&(cons[i]), NULL, &consumer, queue);
    }

    for (i = 0; i < NPROD; i++)
    {
        pthread_join(prod[i], NULL);
    }

    for (i = 0; i < NCONS; i++)
    {
        pthread_join(cons[i], NULL);
    }

    QDestroy(queue);
    return (0);
}

void *producer(void *queue_void)
{
    queue_t *queue = (queue_t*)queue_void;
    size_t thread_id;
    thread_id = __sync_fetch_and_add(&prod_id, 1);

    while (counter < SIZE)
    {
        int data = 1;

        pthread_mutex_lock(&lock);

        /* start of critical section */
        QEnqueue(queue, &data);
        printf("Producer %lu, counter %lu, Queue_size %lu\n", thread_id, counter, QSize(queue));
        counter++;
        /* end of critical section */

        pthread_mutex_unlock(&lock);
        sem_post(&sem);
        sleep(0);
    }

    return (NULL);
}

void *consumer(void *queue_void)
{
    queue_t *queue = (queue_t*)queue_void;
    size_t thread_id;
    thread_id = __sync_fetch_and_add(&cons_id, 1);
    

    while (counter < SIZE)
    {
        sem_wait(&sem);
        pthread_mutex_lock(&lock);

        /* start of critical section */
        printf("Consumer %lu, counter %lu, Queue_size %lu\n", thread_id, counter, QSize(queue));
        QDequeue(queue);
        /* end of critical section */
        
        pthread_mutex_unlock(&lock);
        sleep(0);
    }

    return (NULL);
}