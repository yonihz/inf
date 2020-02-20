// v2.0 20.2.2020 12:04
#ifndef _ILRD_OL734_THREAD_POOL_HPP_
#define _ILRD_OL734_THREAD_POOL_HPP_

#include <queue>                        // std::priority_queue
#include <list>                         // list
#include <utility>                      // pair
#include <boost/function.hpp>           // boost::function
#include <boost/interprocess/sync/interprocess_semaphore.hpp> // boost::semaphore
#include <boost/interprocess/sync/interprocess_mutex.hpp> // boost::mutex
#include <boost/core/noncopyable.hpp>   // boost::noncopyable

#include "waitable_queue.hpp"           // WaitableQueue
#include "thread.hpp"                   // Thread
#include "shared_ptr.hpp"               // shared pointer

namespace ilrd
{

template<typename T>
class Pqueue
{
public:
    Pqueue();
    ~Pqueue();
    void push(const T& toPush);
    void pop();

    const T& front() const;

    typedef const T& const_reference;
    typedef T& reference;

    size_t GetSize() const;

private:
    std::priority_queue<T> m_priorityQueue;
};

class Task
{
public:
    virtual void Execute() =0;
    virtual ~Task() =0;
};

class ThreadPool : private boost::noncopyable
{
public:
    enum priority_t {LOW = 3, MEDIUM = 2, HIGH = 1};

    explicit ThreadPool(std::size_t numOfThreads_);
    ~ThreadPool();

    void SetNumOfThreads(std::size_t numOfThreads_); // waiting for task completion
    void AddTask(SharedPtr<Task> func_, priority_t priority_); 
    void Pause();                               // waiting for task completion
    void Resume();
    void Stop(std::size_t timeOutSeconds_);

private:
    static void *ThreadRoutine(void* arg);

    enum internalPriority_t{
                            RESERVED = 0,
                            INTERNAL_LOW = LOW, 
                            INTERNAL_MEDIUM = MEDIUM,
                            INTERNAL_HIGH = HIGH};
    typedef std::pair<SharedPtr<Task>, internalPriority_t> taskAndPriority_t;

    void AddTask(SharedPtr<Task> func_, internalPriority_t priority_); 
    void Push(Thread* thread_);
    void Remove(Thread* thread_);

    WaitableQueue<Pqueue<taskAndPriority_t> > m_pendingTasks;
    std::list<Thread*> m_threads;
    std::size_t m_numActiveThreads;
    boost::interprocess::interprocess_semaphore m_semaphore;
};

// Pqueue
template<typename T>
Pqueue<T>::Pqueue()
    : m_priorityQueue()
{
}

template<typename T>
Pqueue<T>::~Pqueue()
{
}

template<typename T>
void Pqueue<T>::pop()
{
    m_priorityQueue.pop();
}

template<typename T>
void Pqueue<T>::push(const T& toPush)
{
    m_priorityQueue.push(toPush);
}

template<typename T>
const T& Pqueue<T>::front() const
{
    return this->m_priorityQueue.top();
}

template<typename T>
size_t Pqueue<T>::GetSize() const
{
    return this->m_priorityQueue.size();
}

/******************************************************************************/
/****** ThreadPool ************************************************************/
/******************************************************************************/

ThreadPool::ThreadPool(std::size_t numOfThreads_)
    : m_pendingTasks(), m_threads(), m_semaphore(0) {}

ThreadPool::~ThreadPool()
{
    Stop(0);
}

void ThreadPool::SetNumOfThreads(std::size_t numOfThreads_)
{
    if (numOfThreads_ > m_numActiveThreads)
    {
        std::size_t numThreadsToCreate = numOfThreads_ - m_numActiveThreads;

        for (size_t i = 0; i < numThreadsToCreate; ++i)
        {
            Push(new Thread(ThreadPool::ThreadRoutine, NULL));
        }
    }
    else if (numOfThreads_ < m_numActiveThreads)
    {
        std::size_t numThreadsToRemove = m_numActiveThreads - numOfThreads_;
        for (size_t i = 0; i < numThreadsToRemove; ++i)
        {
            SharedPtr<Task> stopTask(new StopTask);
            AddTask(stopTask, ThreadPool::RESERVED);
        }      
    }

    m_numActiveThreads = numOfThreads_;
}

void ThreadPool::AddTask(SharedPtr<Task> func_, priority_t priority_)
{
    AddTask(func_, static_cast<internalPriority_t>(priority_));
}

void ThreadPool::AddTask(SharedPtr<Task> func_, internalPriority_t priority_)
{
    m_pendingTasks.Push(taskAndPriority_t(func_, priority_));
}

void ThreadPool::Pause()
{

}

void ThreadPool::Resume()
{

}

void ThreadPool::Stop(std::size_t timeOutSeconds_)
{
    for (size_t i = 0; i < m_numActiveThreads; ++i)
    {
        SharedPtr<Task> stopTask(new StopTask);
        AddTask(stopTask, ThreadPool::RESERVED);
    }     
}

void *ThreadPool::ThreadRoutine(void* arg)
{
    ThreadPool *threadPool = static_cast<ThreadPool*>(arg);

    try
    {
        while(1)
        {
            taskAndPriority_t tp;
            threadPool->m_pendingTasks.Pop(tp);
        }
    }
    catch (StopThreadPool &e)
    {
        return;
    }
}

/******************************************************************************/
/****** ThreadPool :: ThreadList **********************************************/
/******************************************************************************/

void ThreadPool::Push(Thread* thread_)
{
    m_threads.push_back(thread_);
}

void ThreadPool::Remove(Thread* thread_)
{
    m_threads.remove(thread_);
}

/******************************************************************************/
/****** Service Tasks *********************************************************/
/******************************************************************************/

class StopTask : public Task
{
public:
    void Execute()
    {
        throw StopThreadPool();
    }
};

class PauseTask : public Task
{
    
};

/******************************************************************************/
/****** Stop Exception ********************************************************/
/******************************************************************************/

class StopThreadPool : public std::runtime_error
{
public:
    StopThreadPool(const std::string& s_ = "Thread pool stopped")
        : runtime_error(s_) { }
};

} // namespace ilrd

#endif // _ILRD_OL734_THREAD_POOL_HPP_