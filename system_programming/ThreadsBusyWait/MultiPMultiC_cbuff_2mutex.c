#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 50
#define SIZE_CBUFF 10
#define NCONS 4
#define NPROD 4

pthread_mutex_t lock_prod, lock_cons;
sem_t sem_used, sem_free;
size_t counter = 0;
size_t prod_id = 1, cons_id = 1;

typedef struct
{
    int *arr;
    size_t cap;
    size_t size;
    size_t read_idx;
    size_t write_idx;
} cbuff_t;


void *producer(void *cbuff_void);
void *consumer(void *cbuff_void);

cbuff_t *CBuffCreate(size_t size);
int CBuffRead(cbuff_t *cbuff);
void CBuffWrite(cbuff_t *cbuff, int data);
void CBuffDestroy(cbuff_t *cbuff);

int main()
{
    pthread_t prod[NPROD];
    pthread_t cons[NCONS];
    size_t i = 0;
    cbuff_t *cbuff = NULL;

    pthread_mutex_init(&lock_prod, NULL);
    pthread_mutex_init(&lock_cons, NULL);
    sem_init(&sem_used, 0, 0);
    sem_init(&sem_free, 0, SIZE_CBUFF);

    cbuff = CBuffCreate(SIZE_CBUFF);

    for (i = 0; i < NPROD; i++)
    {
        pthread_create(&(prod[i]), NULL, &producer, cbuff);
    }

    for (i = 0; i < NCONS; i++)
    {
        pthread_create(&(cons[i]), NULL, &consumer, cbuff);
    }

    for (i = 0; i < NPROD; i++)
    {
        pthread_join(prod[i], NULL);
    }

    for (i = 0; i < NCONS; i++)
    {
        pthread_join(cons[i], NULL);
    }

    CBuffDestroy(cbuff);

    return (0);
}

void *producer(void *cbuff_void)
{
    size_t thread_id;
    cbuff_t *cbuff = (cbuff_t*)cbuff_void;
    thread_id = __sync_fetch_and_add(&prod_id, 1);

    while (counter < SIZE)
    {
        int data = 1;

        sem_wait(&sem_free);
        pthread_mutex_lock(&lock_prod);

        /* start of critical section */
        CBuffWrite(cbuff, data);
        printf("Producer %lu, counter %lu, CBUff_size %lu\n", thread_id, counter, cbuff->size);
        counter++;
        /* end of critical section */

        pthread_mutex_unlock(&lock_prod);
        sleep(0);
        sem_post(&sem_used);
    }

    return (NULL);
}

void *consumer(void *cbuff_void)
{
    size_t thread_id;
    cbuff_t *cbuff = (cbuff_t*)cbuff_void;
    thread_id = __sync_fetch_and_add(&cons_id, 1);
    
    while (counter < SIZE)
    {
        sem_wait(&sem_used);
        pthread_mutex_lock(&lock_cons);

        /* start of critical section */
        printf("Consumer %lu, counter %lu, CBUff_size %lu\n", thread_id, counter, cbuff->size);
        CBuffRead(cbuff);
        /* end of critical section */
        
        pthread_mutex_unlock(&lock_cons);
        sleep(0);
        sem_post(&sem_free);
    }

    return (NULL);
}

cbuff_t *CBuffCreate(size_t size)
{
    int *arr = NULL;
    cbuff_t *cbuff = NULL;

    cbuff = malloc(sizeof(cbuff_t));

    arr = malloc(size * sizeof(int));

    cbuff->arr = arr;
    cbuff->read_idx = 0;
    cbuff->size = 0;
    cbuff->cap = size;

    return cbuff;
}

int CBuffRead(cbuff_t *cbuff)
{
    int read_val = 0;
    if (cbuff->size == 0)
    {
        printf("Read error: cbuff is empty\n");
        return 0;
    }

    read_val = cbuff->arr[cbuff->read_idx];
    cbuff->size -= 1;
    cbuff->read_idx = (cbuff->read_idx + 1) % cbuff->cap;
    return read_val;
}

void CBuffWrite(cbuff_t *cbuff, int data)
{
    if (cbuff->size == cbuff->cap)
    {
        printf("Write error: cbuff is full\n");
        return;
    }

    cbuff->size += 1;
    cbuff->arr[cbuff->write_idx] = data;
    cbuff->write_idx = (cbuff->write_idx + 1) % cbuff->cap;
    return;
}

void CBuffDestroy(cbuff_t *cbuff)
{
    free(cbuff->arr);
    free(cbuff);
}