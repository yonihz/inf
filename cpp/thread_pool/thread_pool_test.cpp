#include <iostream>

#include "thread_pool.hpp"

using namespace ilrd;

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
    std::size_t wait_time = 0;
    ThreadPool threadPool(4);

    Task *task_ptr1 = new PrintTask("Task1", 1, 5);
    Task *task_ptr2 = new PrintTask("Task2", 1, 5);
    Task *task_ptr3 = new PrintTask("Task3", 1, 60);
    Task *task_ptr4 = new PrintTask("Task4", 1, 60);
    Task *task_ptr5 = new PrintTask("Task5", 1, 60);
    Task *task_ptr6 = new PrintTask("Task6", 1, 60);
    Task *task_ptr7 = new PrintTask("Task7", 1, 60);
    Task *task_ptr8 = new PrintTask("Task8", 1, 60);

    threadPool.AddTask(SharedPtr<Task>(task_ptr1), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr2), ThreadPool::HIGH);

    wait_time = 1;
    while (wait_time)
    {
        wait_time = sleep(wait_time);
    }

    threadPool.Pause();

    threadPool.AddTask(SharedPtr<Task>(task_ptr3), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr4), ThreadPool::HIGH);
    

    wait_time = 6;
    while (wait_time)
    {
        wait_time = sleep(wait_time);
    }

    threadPool.Resume();

    wait_time = 5;
    while (wait_time)
    {
        wait_time = sleep(wait_time);
    }

    threadPool.SetNumOfThreads(6);

    threadPool.AddTask(SharedPtr<Task>(task_ptr5), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr6), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr7), ThreadPool::HIGH);
    threadPool.AddTask(SharedPtr<Task>(task_ptr8), ThreadPool::HIGH);

    wait_time = 20;
    while (wait_time)
    {
        wait_time = sleep(wait_time);
    }

    threadPool.Stop(5);
}

PrintTask::PrintTask(std::string str_, std::size_t period_, std::size_t times_)
    : m_str(str_), m_period(period_), m_times(times_) {}

void PrintTask::Execute()
{
    for (std::size_t i = 0; i < m_times; ++i)
    {
        std::size_t time_left = m_period;
        while (time_left)
        {
            time_left = sleep(time_left);
        }

        std::cout << m_str << std::endl;
    }    
}