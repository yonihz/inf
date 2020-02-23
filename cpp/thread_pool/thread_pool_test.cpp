// gd98 thread_pool_test.cpp ../thread/thread.cpp ../logger/logger.cpp -I../shared_ptr/ -I../waitable_queue/ -I../thread/ -I../singleton/ -I../logger/ -pthread

#include <iostream>

#include "thread_pool.hpp"
#include "logger.hpp"
#include "singleton.hpp"

using namespace ilrd;

void Test1();
void Test2();

void sig_handler_main(int sig)
{
    UNUSED(sig);
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.Log(Logger::DEBUG, "main got SIGUSR1\n");
}

class PrintTask : public Task
{
public:
    PrintTask(std::string str_, std::size_t period_, std::size_t times_);

    void Execute();

private:
    std::string m_str;
    std::size_t m_period;
    std::size_t m_times;
};

int main()
{
    Test1();
    // Test2();

    return 0;
}

void Test1()
{
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.Log(Logger::DEBUG, "----------\nAddTask and Pause/Resume tests\n----------\n");

    struct sigaction sa1;
    sa1.sa_handler = &sig_handler_main;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    std::size_t wait_time = 0;
    ThreadPool threadPool(4);

    Task *task_ptr1 = new PrintTask("Task1", 1, 3);
    Task *task_ptr2 = new PrintTask("Task2", 1, 3);
    Task *task_ptr3 = new PrintTask("Task3", 1, 60);
    Task *task_ptr4 = new PrintTask("Task4", 1, 60);

    logger.Log(Logger::DEBUG, "Added 2 tasks (Task1, Task2) that run for 3 seconds\n");
    threadPool.AddTask(SharedPtr<Task>(task_ptr1), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr2), ThreadPool::HIGH);

    wait_time = 1;
    while (wait_time)
    {
        wait_time = sleep(wait_time);
    }

    logger.Log(Logger::DEBUG, "Sent pause and resume after 5 seconds\n");
    threadPool.Pause();

    wait_time = 1;
    while (wait_time)
    {
        wait_time = sleep(wait_time);
    }

    logger.Log(Logger::DEBUG, "Added 2 tasks (Task3, Task4) that run for 60 seconds\n");
    threadPool.AddTask(SharedPtr<Task>(task_ptr3), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr4), ThreadPool::HIGH);
    
    wait_time = 5;
    while (wait_time)
    {
        wait_time = sleep(wait_time);
    }

    logger.Log(Logger::DEBUG, "Sent resume\n");
    threadPool.Resume();

    wait_time = 4;
    while (wait_time)
    {
        wait_time = sleep(wait_time);
    }

    // Dtor is called, which calls Stop(0)
}

void Test2()
{
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.Log(Logger::DEBUG, "----------\nStop test\n----------\n");
    logger.Log(Logger::DEBUG, "Added 2 tasks (Task1, Task2) that run for 3 seconds\n");
    logger.Log(Logger::DEBUG, "Added 2 tasks (Task3, Task4) that run for 30 seconds\n");
    logger.Log(Logger::DEBUG, "Sent Stop(6)\n");
    struct sigaction sa1;
    sa1.sa_handler = &sig_handler_main;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    ThreadPool threadPool(4);

    Task *task_ptr1 = new PrintTask("Task1", 1, 3);
    Task *task_ptr2 = new PrintTask("Task2", 1, 3);
    Task *task_ptr3 = new PrintTask("Task3", 1, 30);
    Task *task_ptr4 = new PrintTask("Task4", 1, 30);

    threadPool.AddTask(SharedPtr<Task>(task_ptr1), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr2), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr3), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr4), ThreadPool::HIGH);

    std::size_t wait_time = 1;
    while (wait_time)
    {
        wait_time = sleep(wait_time);
    }

    threadPool.Stop(6);
}

PrintTask::PrintTask(std::string str_, std::size_t period_, std::size_t times_)
    : m_str(str_), m_period(period_), m_times(times_) {}

void PrintTask::Execute()
{
    Logger &logger = *(Singleton<Logger>::Instance());

    for (std::size_t i = 0; i < m_times; ++i)
    {
        std::size_t time_left = m_period;
        while (time_left)
        {
            time_left = sleep(time_left);
        }

        logger.Log(Logger::DEBUG, m_str + "\n");
    }    
}