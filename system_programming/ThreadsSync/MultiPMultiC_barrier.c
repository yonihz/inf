#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 1000
#define NCONS 4

pthread_mutex_t lock;
pthread_cond_t cond;
sem_t sem;
size_t counter = 0;
size_t cons_id = 1;
size_t data = 0;


void *producer(void *param);
void *consumer(void *param);

int main()
{
    pthread_t prod;
    pthread_t cons[NCONS];
    size_t i = 0;

    pthread_mutex_init(&lock, NULL);
    sem_init(&sem, 0, 0);

    pthread_create(&prod, NULL, &producer, NULL);

    for (i = 0; i < NCONS; ++i)
    {
        pthread_create(&(cons[i]), NULL, &consumer, NULL);
    }

    for (i = 0; i < NCONS; ++i)
    {
        pthread_join(cons[i], NULL);
    }

    pthread_join(prod, NULL);

    return (0);
}


void *producer(void *param)
{
    size_t i = 0;
    size_t j = 0;

    (void)(param);

    for (j = 0; j < SIZE; j++)
    {
        pthread_mutex_lock(&lock);
        counter = 0;
        ++(data);
        printf("Producer: %lu\n", data);

        for (i = 0; i < NCONS; ++i)
        {
            sem_post(&sem);
        }

        while (counter < NCONS)
        {
            pthread_cond_wait(&cond, &lock);
        }
        
        pthread_mutex_unlock(&lock);
    }

    return (NULL);
}

void *consumer(void *param)
{
    size_t thread_id;
    size_t j = 0;
    thread_id = __sync_fetch_and_add(&cons_id, 1);
    
    (void)(param);

    for (j = 0; j < SIZE; j++)
    {
        sem_wait(&sem);
        pthread_mutex_lock(&lock);

        printf("Consumer %lu: %lu\n", thread_id, data);

        ++counter;

        if (counter < NCONS)
        {
            pthread_cond_wait(&cond, &lock);
        }
        else
        {
            pthread_cond_broadcast(&cond);
        }
        
        pthread_mutex_unlock(&lock);
    }

    return (NULL);
}


/*
void *producer(void *data)
{
    size_t i = 0;

    while (*(size_t*)data < (size_t)SIZE)
    { 
        pthread_mutex_lock(&lock);

        ++(*(size_t*)data);
        printf("Producer: %lu\n", *(size_t*)data);

        for (i = 0; i < NCONS; i++)
        {
            sem_post(&sem);
        }

        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }

    return (NULL);
}

void *consumer(void *data)
{
    size_t thread_id;
    thread_id = __sync_fetch_and_add(&cons_id, 1);
    

    while (*(size_t*)data < SIZE)
    {
        sem_wait(&sem);
        pthread_mutex_lock(&lock);
        counter++;
        pthread_cond_wait(&cond, &lock);


        printf("Consumer %lu: %lu\n", thread_id, *(size_t*)data);

        
        pthread_mutex_unlock(&lock);
    }

    return (NULL);
}
*/
