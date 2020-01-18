#include <iostream>
#include <unistd.h>

#include "thread.hpp"

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

void *TestThread1(void *arg);
void *TestThread2(void *arg);

void TestNoLeaks();
void TestExceptionDetachJoin();
void TestExceptionDoubleJoin();
void TestExceptionJoinDetach();
void TestExceptionMemory();

int main()
{
    TestNoLeaks();
    TestExceptionDetachJoin();
    TestExceptionDoubleJoin();
    TestExceptionJoinDetach();
    TestExceptionMemory();

    return 0;
}

void TestNoLeaks()
{
    std::cout << "Test is successful if valgrind shows no leaks" << std::endl;
    ilrd::Thread th1(TestThread2, NULL);
    std::cout << "Thread ID: " << th1.GetID() << std::endl; 
    sleep(2);
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
        REQUIRE(static_cast<std::string>(e.what()) == 
            static_cast<std::string>(ilrd::NonJoinable().what()),
            "Join after Detach");
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
        REQUIRE(static_cast<std::string>(e.what()) == 
        static_cast<std::string>(ilrd::ThreadException().what()),
        "Detach after join");
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
        REQUIRE(static_cast<std::string>(e.what()) == 
        static_cast<std::string>(ilrd::ThreadException().what()),
        "Double Join");        
        std::cerr << e.what() << std::endl;
    }
}

void TestExceptionMemory()
{
    try
    {
        pthread_attr_t pattr;
        pthread_attr_init(&pattr);
        pthread_attr_setstacksize(&pattr, 1e10);
        Thread::Attr attr(pattr);

        ilrd::Thread(TestThread1, NULL, attr);
    }
    catch(const std::exception& e)
    {
        REQUIRE(static_cast<std::string>(e.what()) == 
        static_cast<std::string>(ilrd::NoResource().what()),
        "Insufficient resources");                
        std::cerr << e.what() << '\n';
    }
}

void *TestThread1(void *arg)
{
    (void)(arg);
    write(0, "Test thread\n", 12);
    return NULL;
}

void *TestThread2(void *arg)
{
    (void)(arg);
    sleep(1);
    std::cout << "Self ID: " << ilrd::Thread::GetIDSelf() << std::endl;
    return NULL;
}
