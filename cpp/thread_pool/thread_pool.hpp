// v2.0 20.2.2020 12:04
#ifndef _ILRD_OL734_THREAD_POOL_HPP_
#define _ILRD_OL734_THREAD_POOL_HPP_

#include <queue>                        // std::priority_queue
#include <vector>                       // std::vector
#include <list>                         // std:;list
#include <utility>                      // std::pair
#include <signal.h>                     // pthread_kill
#include <boost/function.hpp>           // boost::function
#include <boost/core/noncopyable.hpp>   // boost::noncopyable
#include <boost/interprocess/sync/interprocess_mutex.hpp>       // boost::mutex
#include <boost/interprocess/sync/interprocess_semaphore.hpp>   // boost::semaphore

#include "waitable_queue.hpp"
#include "thread.hpp"
#include "shared_ptr.hpp"
#include "logger.hpp"
#include "singleton.hpp"

#define UNUSED(x) (void)(x)

namespace ilrd
{

/******************************************************************************/
/****** Pqueue ****************************************************************/
/******************************************************************************/

template<typename T, class Compare>
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
    std::priority_queue<T, std::vector<T>, Compare> m_priorityQueue;
};

/******************************************************************************/
/****** Task ******************************************************************/
/******************************************************************************/

class Task
{
public:
    virtual void Execute() =0;
    virtual ~Task() =0;
};

Task::~Task() {}

/******************************************************************************/
/****** ThreadPool ************************************************************/
/******************************************************************************/

// Not thread-safe

class ThreadPool : private boost::noncopyable
{
public:
    enum priority_t {LOW = 3, MEDIUM = 2, HIGH = 1};

    explicit ThreadPool(std::size_t numOfThreads_);
    ~ThreadPool();

    void SetNumOfThreads(std::size_t numOfThreads_); // waiting for task completion
    void AddTask(SharedPtr<Task> task_, priority_t priority_); 
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

    class ComparePriority
    {
    public:
        bool operator()(const taskAndPriority_t &lhs_, const taskAndPriority_t &rhs_)
        {
          return (lhs_.second > rhs_.second);
        }   
    };

    void AddTask(SharedPtr<Task> task_, internalPriority_t priority_); 
    void Push(Thread* thread_);
    void Remove(Thread* thread_);

    WaitableQueue<Pqueue<taskAndPriority_t, ComparePriority> > m_pendingTasks;
    std::list<Thread*> m_threads;
    boost::interprocess::interprocess_semaphore m_semaphore;
    std::size_t m_numActiveThreads;

    friend class PauseTask;
};

/******************************************************************************/
/****** Pqueue ****************************************************************/
/******************************************************************************/

template<typename T, class Compare>
Pqueue<T, Compare>::Pqueue()
    : m_priorityQueue()
{
}

template<typename T, class Compare>
Pqueue<T, Compare>::~Pqueue()
{
}

template<typename T, class Compare>
void Pqueue<T, Compare>::pop()
{
    m_priorityQueue.pop();
}

template<typename T, class Compare>
void Pqueue<T, Compare>::push(const T& toPush)
{
    m_priorityQueue.push(toPush);
}

template<typename T, class Compare>
const T& Pqueue<T, Compare>::front() const
{
    return this->m_priorityQueue.top();
}

template<typename T, class Compare>
size_t Pqueue<T, Compare>::GetSize() const
{
    return this->m_priorityQueue.size();
}

/******************************************************************************/
/****** Stop Exception ********************************************************/
/******************************************************************************/

class StopThreadPool : public std::runtime_error
{
public:
    StopThreadPool(const std::string& s_ = "Thread pool stopped")
        : runtime_error(s_) { }
};

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
public:
    PauseTask(ThreadPool &threadPool_)
        : m_threadPool(threadPool_) {}

    void Execute()
    {
        m_threadPool.m_semaphore.wait();
    }

private:
    ThreadPool &m_threadPool;  
};

/******************************************************************************/
/****** ThreadPool ************************************************************/
/******************************************************************************/

ThreadPool::ThreadPool(std::size_t numOfThreads_)
    : m_pendingTasks(), m_threads(), m_semaphore(0), m_numActiveThreads(0)
{
    SetNumOfThreads(numOfThreads_);
}

ThreadPool::~ThreadPool()
{
    // kills all threads immediately
    Stop(0);
}

void ThreadPool::SetNumOfThreads(std::size_t numOfThreads_)
{
    // adds new threads to list
    if (numOfThreads_ > m_numActiveThreads)
    {
        std::size_t numThreadsToCreate = numOfThreads_ - m_numActiveThreads;

        for (size_t i = 0; i < numThreadsToCreate; ++i)
        {
            Push(new Thread(ThreadPool::ThreadRoutine, this));
        }
    }
    // add stop tasks to tasks queue
    // threads are ended but not removed from thread list or joined (become zombies)
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

void ThreadPool::AddTask(SharedPtr<Task> task_, priority_t priority_)
{
    AddTask(task_, static_cast<internalPriority_t>(priority_));
}

void ThreadPool::AddTask(SharedPtr<Task> task_, internalPriority_t priority_)
{
    m_pendingTasks.Push(taskAndPriority_t(task_, priority_));
}

void ThreadPool::Pause()
{
    for (size_t i = 0; i < m_numActiveThreads; ++i)
    {
        SharedPtr<Task> pauseTask(new PauseTask(*this));
        AddTask(pauseTask, ThreadPool::RESERVED);
    }     
}

void ThreadPool::Resume()
{
    for (std::size_t i = 0; i < m_numActiveThreads; ++i)
    {
        m_semaphore.post();
    }
}

void ThreadPool::Stop(std::size_t timeOutSeconds_)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    for (size_t i = 0; i < m_numActiveThreads; ++i)
    {
        SharedPtr<Task> stopTask(new StopTask);
        AddTask(stopTask, ThreadPool::RESERVED);
    }

    std::list<Thread*>::iterator it;
    std::list<Thread*>::iterator it_end = m_threads.end();
    std::size_t numSuccessfulJoins = 0;
    std::size_t sizeThreadList = m_threads.size();

    for (it = m_threads.begin(); it != it_end; ++it)
    {
        numSuccessfulJoins += ((*it)->TryJoin(NULL) == 0);
    }

    if (numSuccessfulJoins == sizeThreadList)
    {
        return;
    }

    while (timeOutSeconds_)
    {
        timeOutSeconds_ = sleep(timeOutSeconds_);
    }

    for (it = m_threads.begin(); it != it_end; ++it)
    {
        logger.Log(Logger::DEBUG, "Sending SIGUSR1\n");
        pthread_kill((*it)->GetID(), SIGUSR1);
    }
}

void ThreadPool::Push(Thread* thread_)
{
    m_threads.push_back(thread_);
}

void ThreadPool::Remove(Thread* thread_)
{
    m_threads.remove(thread_);
}

/******************************************************************************/
/****** Thread routine and signal handler *************************************/
/******************************************************************************/


void sig_handler1(int sig)
{
    UNUSED(sig);
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.Log(Logger::DEBUG, "Thread got SIGUSR1\n");
    pthread_exit(NULL);
}

void *ThreadPool::ThreadRoutine(void* arg)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    ThreadPool *threadPool = static_cast<ThreadPool*>(arg);

    struct sigaction sa1;
    sa1.sa_handler = &sig_handler1;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    try
    {
        while(1)
        {
            taskAndPriority_t tp = std::make_pair(SharedPtr<Task>(NULL), RESERVED);
            threadPool->m_pendingTasks.Pop(tp);
            tp.first->Execute();
        }
    }
    catch (const StopThreadPool &e)
    {
        logger.Log(Logger::DEBUG, std::string(e.what()) + "\n");
    }

    return NULL;
}

} // namespace ilrd

#endif // _ILRD_OL734_THREAD_POOL_HPP_