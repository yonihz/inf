#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define SIZE 10

sig_atomic_t is_ready = 0;
size_t counter = 0;

void *producer(void *base);
void *consumer(void *base);

int main()
{
    pthread_t prod, cons;

    size_t arr[SIZE] = {0};

    pthread_create(&prod, NULL, &producer, arr);
    pthread_create(&cons, NULL, &consumer, arr);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return (0);
}

void *producer(void *base)
{
    size_t i = 0;

    for (counter = 0; counter < SIZE; counter++)
    {
        while (1 == is_ready);

        /* critical section */
        for (i = 0; i < SIZE; i++)
        {
            *((size_t*)(base) + i) = counter;
        }

        is_ready = 1;
    }

    return (NULL);
}

void *consumer(void *base)
{
    size_t i = 0;
    size_t sum = 0;

    while (counter < SIZE)
    {
        while (0 == is_ready);

        /* critical section */
        sum = 0;
        for (i = 0; i < SIZE; i++)
        {
            sum += *((size_t*)(base) + i);
        }
        printf("Sum = %lu\n", sum);
        is_ready = 0;
    }

    return (NULL);
}