#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "lock_guard.hpp"

void ProducerThread();
void ConsumerThread();

std::mutex mutex_lock;
size_t counter;
const size_t counter_size = 100;

int main()
{
    const size_t nproducers = 10;
    const size_t nconsumers = 10;
    
    std::vector<std::thread> producer_vector;
    std::vector<std::thread> consumer_vector;

    for (size_t i = 0; i < nproducers; ++i)
    {
        producer_vector.push_back(std::thread(ProducerThread));
    }

    for (size_t i = 0; i < nconsumers; ++i)
    {
        consumer_vector.push_back(std::thread(ConsumerThread));
    }

    for (size_t i = 0; i < nproducers; ++i)
    {
        producer_vector[i].join();
    }

    for (size_t i = 0; i < nconsumers; ++i)
    {
        consumer_vector[i].join();
    }

    return 0;
}

void ProducerThread()
{
    while (counter < counter_size)
    {
        ilrd::LockGuard<std::mutex> lg(mutex_lock); 

        /* start of critical section */
        std::cout << "Producer Thread ID: " << std::this_thread::get_id() << " counter: " << counter << std::endl;
        ++counter;
        /* end of critical section */
    }
}

void ConsumerThread()
{
    while (counter < counter_size)
    {
        ilrd::LockGuard<std::mutex> lg(mutex_lock); 

        /* start of critical section */
        std::cout << "Consumer Thread ID: " << std::this_thread::get_id() << " counter: " << counter << std::endl;
        ++counter;
        /* end of critical section */
    }
}