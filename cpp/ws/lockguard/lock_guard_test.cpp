#include <iostream>
#include <mutex>

#include "lock_guard.hpp"
#include "thread.hpp"

#define COUNTER_SIZE 10
#define NPRODUCERS 4

using namespace ilrd;

LockGuard<std::mutex> lg(std::mutex);
size_t counter;

int main()
{
    Thread th_array[NPRODUCERS] = {
        Thread(producer, NULL),
        Thread(producer, NULL),
        Thread(producer, NULL),
        Thread(producer, NULL)};

    for (size_t i = 0; i < NPRODUCERS; ++i)
    {
        th_array[i].Join();
    }

    return 0;
}

void *producer(void *)
{
    while (counter < COUNTER_SIZE)
    {
        int data = 1;

        pthread_mutex_lock(&lock);        

        /* start of critical section */
        std::cout << "Thread ID: " << 
        QEnqueue(queue, &data);
        printf("Producer %lu, counter %lu, Queue_size %lu\n", thread_id, counter, QSize(queue));
        is_empty = 0;
        counter++;
        /* end of critical section */

        pthread_mutex_unlock(&lock);
        sleep(0);
    }

    return (NULL);
}