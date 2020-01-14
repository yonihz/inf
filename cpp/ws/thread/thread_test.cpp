#include <iostream>
#include <unistd.h>

#include "thread.hpp"

void *TestThread1(void *arg);
void *TestThread2(void *arg);

void TestNoLeaks();
void TestGetID();
void TestExceptionDetachJoin();
void TestExceptionDoubleJoin();
void TestExceptionJoinDetach();
void TestExceptionDeadlock();
void TestExceptionMemory();

int main()
{
    TestNoLeaks();
    // TestGetID();
    // TestExceptionDetachJoin();
    // TestExceptionDoubleJoin();
    // TestExceptionJoinDetach();
    // TestExceptionDeadlock();
    // TestExceptionMemory();

    return 0;
}

void TestExceptionDeadlock()
{
    try
    {
        ilrd::Thread th1(TestThread2, NULL);
    }
    catch(const ilrd::ThreadException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void TestExceptionDetachJoin()
{
    try
    {
        ilrd::Thread th1(TestThread1, NULL);
        th1.Detach();
        th1.Join();
    }
    catch(const ilrd::ThreadException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void TestExceptionJoinDetach()
{
    try
    {
        ilrd::Thread th1(TestThread1, NULL);
        th1.Join();
        th1.Detach();
    }
    catch(const ilrd::ThreadException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void TestExceptionDoubleJoin()
{
    try
    {
        ilrd::Thread th1(TestThread1, NULL);
        th1.Join();
        th1.Join();
    }
    catch(const ilrd::ThreadException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void TestGetID()
{
    ilrd::Thread th1(TestThread1, NULL);
    ilrd::Thread th2(TestThread1, NULL);
    std::cout << th1.GetID() << std::endl;
    std::cout << th2.GetID() << std::endl;
}

void TestNoLeaks()
{
    ilrd::Thread th1(TestThread1, NULL);
    ilrd::Thread th2(TestThread1, NULL);
    ilrd::Thread th3(TestThread1, NULL);
    ilrd::Thread th4(TestThread1, NULL);
    ilrd::Thread th5(TestThread1, NULL);
}

void TestExceptionMemory()
{
    std::cout << "test 100k threads" << std::endl;
    try
    {
        for (size_t i = 0; i < 100000; ++i)
        {
            ilrd::Thread(TestThread1, NULL);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void *TestThread1(void *arg)
{
    (void)(arg);
    std::cout << "Test" << std::endl;
    sleep(2);
    return NULL;
}

void *TestThread2(void *arg)
{
    (void)(arg);
    std::cout << "Test" << std::endl;
    throw ilrd::Deadlock();
    return NULL;
}
