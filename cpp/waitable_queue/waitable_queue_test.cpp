// compile command:
// gd98 ../thread/thread.cpp waitable_queue_test.cpp -pthread -I../thread/

#include <iostream>
#include <queue>

#include <boost/core/noncopyable.hpp>

#include "thread.hpp"
#include "waitable_queue.hpp"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define MAG  "\x1B[35m"
#define RESET "\x1B[0m"

void REQUIRE(bool test, const char test_name[])
{
	(true == test) ?
	std::cout << GRN << "TEST PASS: " << test_name << std::endl :
	std::cout << RED << "TEST FAIL: " << test_name << std::endl;
    std::cout << RESET;
}

using namespace ilrd;

void *writer1(void *thread_ret);
void *writer2(void *thread_ret);
void *reader1(void *thread_ret);
void *reader2(void *thread_ret);

void TestTimeoutSum1();
void TestTimeoutSum2();

boost::interprocess::interprocess_semaphore sem(0);
WaitableQueue< std::queue<int> > q1;
WaitableQueue< std::queue<int> > q2;
int g_counter = 0;

int main()
{
    TestTimeoutSum1();
    TestTimeoutSum2();
}

void TestTimeoutSum1()
{
    sem.post();
    g_counter = 0;
    const size_t nthreads = 1000;
    
    Thread *writers_arr[nthreads];
    Thread *readers_arr[nthreads];

    int sum = 0;

    for (size_t i = 0; i < nthreads; ++i)
    {
        writers_arr[i] = new Thread(writer1, NULL);

        int *thread_ret = new int;
        readers_arr[i] = new Thread(reader1, thread_ret);
    }

    for (size_t i = 0; i < nthreads; ++i)
    {
        writers_arr[i]->Join();
        delete writers_arr[i];

        int *thread_ret = static_cast<int*>(readers_arr[i]->Join());
        sum += *thread_ret;

        delete thread_ret;
        delete readers_arr[i];
    }

    std::cout << "Test1: timeout = 1sec, expected sum = " 
        << (nthreads*(1 + nthreads) / 2) << ", test sum = " << sum << std::endl;
    REQUIRE(sum != (nthreads*(1 + nthreads) / 2), "Sum of all popped items");
}

void TestTimeoutSum2()
{
    sem.post();
    g_counter = 0;
    const size_t nthreads = 1000;
    
    Thread *writers_arr[nthreads];
    Thread *readers_arr[nthreads];

    int sum = 0;

    for (size_t i = 0; i < nthreads; ++i)
    {
        writers_arr[i] = new Thread(writer2, NULL);
    }

    for (size_t i = 0; i < nthreads; ++i)
    {
        int *thread_ret = new int;
        readers_arr[i] = new Thread(reader2, thread_ret);
    }

    for (size_t i = 0; i < nthreads; ++i)
    {
        writers_arr[i]->Join();
        delete writers_arr[i];
    }

    for (size_t i = 0; i < nthreads; ++i)
    {
        int *thread_ret = static_cast<int*>(readers_arr[i]->Join());
        sum += *thread_ret;

        delete thread_ret;
        delete readers_arr[i];
    }

    std::cout << "Test2: timeout = 3sec, expected sum = " 
        << (nthreads*(1 + nthreads) / 2) << ", test sum = " << sum << std::endl;
    REQUIRE(sum == (nthreads*(1 + nthreads) / 2), "Sum of all popped items");
}

void *writer1(void *thread_ret)
{
    (void)(thread_ret);

    sem.wait();
    ++g_counter;
    int i = g_counter;
    sem.post();
    
    sleep(1);
    q1.Push(i);

    return NULL;
}

void *writer2(void *thread_ret)
{
    (void)(thread_ret);

    sem.wait();
    ++g_counter;
    int i = g_counter;
    sem.post();
    
    sleep(2);
    q2.Push(i);

    return NULL;
}

void *reader1(void *thread_ret)
{
    int pop_ret = 0;
    q1.Pop(pop_ret, 2);
    *(int*)thread_ret = pop_ret;
    return thread_ret;
}

void *reader2(void *thread_ret)
{
    int pop_ret = 0;
    q2.Pop(pop_ret, 3);
    *(int*)thread_ret = pop_ret;
    return thread_ret;
}