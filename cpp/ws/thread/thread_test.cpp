#include <iostream>

#include <unistd.h>

#include "thread.hpp"

using namespace ilrd;

void *TestThread1(void *arg);

void TestGetID();
void TestExceptionDetachJoin();
void TestExceptionDoubleJoin();

int main()
{
    // TestGetID();
    // TestExceptionDetachJoin();
    TestExceptionDoubleJoin();

    return 0;
}

void TestExceptionDetachJoin()
{
    try
    {
        Thread th1(TestThread1, NULL);
        th1.Detach();
        th1.Join();
    }
    catch(const ThreadException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void TestExceptionDoubleJoin()
{
    try
    {
        Thread th1(TestThread1, NULL);
        th1.Join();
        th1.Join();
    }
    catch(const ThreadException& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void TestGetID()
{
    Thread th1(TestThread1, NULL);
    Thread th2(TestThread1, NULL);
    std::cout << th1.GetID() << std::endl;
    std::cout << th2.GetID() << std::endl;
}

void *TestThread1(void *arg)
{
    (void)(arg);
    std::cout << "Test" << std::endl;
    sleep(2);
    return NULL;
}
