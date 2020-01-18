// compile command:
// gd98 ../thread/thread.cpp lock_guard_test.cpp -pthread -I../thread/

#include <iostream>

#include <boost/interprocess/sync/interprocess_mutex.hpp>

#include "lock_guard.hpp"
#include "thread.hpp"

using namespace ilrd;

void *writer(void *);
void *reader(void *);

boost::interprocess::interprocess_mutex mutex_lock;
size_t counter;
const size_t counter_size = 50;

int main()
{
    const size_t nwriters = 10;
    const size_t nreaders = 10;
    
    Thread *writers_arr[nwriters];
    Thread *readers_arr[nreaders];

    for (size_t i = 0; i < nwriters; ++i)
    {
        writers_arr[i] = new Thread(writer, NULL);
    }

    for (size_t i = 0; i < nreaders; ++i)
    {
        readers_arr[i] = new Thread(reader, NULL);
    }

    for (size_t i = 0; i < nwriters; ++i)
    {
        writers_arr[i]->Join();
        delete writers_arr[i];
    }

    for (size_t i = 0; i < nreaders; ++i)
    {
        readers_arr[i]->Join();
        delete readers_arr[i];
    }

    return 0;
}

void *writer(void *)
{
    while (counter < counter_size)
    {
        ilrd::LockGuard<boost::interprocess::interprocess_mutex> lg(mutex_lock); 

        /* start of critical section */
        std::cout << "Producer Thread ID: " << Thread::GetIDSelf() << " counter: " << counter << std::endl;
        ++counter;
        /* end of critical section */
    }

    return NULL;
}

void *reader(void *)
{
    while (counter < counter_size)
    {
        ilrd::LockGuard<boost::interprocess::interprocess_mutex> lg(mutex_lock); 

        /* start of critical section */
        std::cout << "Consumer Thread ID: " << Thread::GetIDSelf() << " counter: " << counter << std::endl;
        ++counter;
        /* end of critical section */
    }

    return NULL;
}