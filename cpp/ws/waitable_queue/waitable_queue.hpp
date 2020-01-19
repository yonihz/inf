#ifndef _ILRD_RD734_WAITABLE_QUEUE_HPP_
#define _ILRD_RD734_WAITABLE_QUEUE_HPP_

#include <boost/core/noncopyable.hpp>   // noncopyable class
#include <boost/interprocess/sync/interprocess_mutex.hpp>   // boost mutex
#include <boost/interprocess/sync/interprocess_semaphore.hpp>   //boost sem
#include <boost/date_time/posix_time/posix_time.hpp>    // boost time

namespace ilrd
{

template<typename Container> 
class WaitableQueue : private boost::noncopyable
{
public:
    explicit WaitableQueue();
    ~WaitableQueue();

    void Push(typename Container::const_reference value_);

    void Pop(typename Container::reference outparam_);
    bool Pop(typename Container::reference outparam_, size_t timeout_);

private:
    Container m_queue;

    boost::interprocess::interprocess_mutex m_mutex;
    boost::interprocess::interprocess_semaphore m_semaphore;
};

/**
 * @brief Construct a new Waitable Queue< Container>:: Waitable Queue object
 * 
 * @tparam Container that stores elements in a queue data structure, and must
 * provide the following methods: front(), push(), pop()
 */

template<typename Container>
WaitableQueue<Container>::WaitableQueue()
    : m_queue(), m_mutex(), m_semaphore(0)
{
}

/**
 * @brief Destroy the Waitable Queue< Container>:: Waitable Queue object
 * 
 * @tparam Container - same as was used in the constructor
 */

template<typename Container>
WaitableQueue<Container>::~WaitableQueue()
{
}

/**
 * @brief Push element to the back of the queue
 * 
 * @tparam Container - same as was used in the constructor
 * @param value_ to be pushed
 * 
 * @throw interprocess_exception on error
 */

template<typename Container>
void WaitableQueue<Container>::Push(typename Container::const_reference value_)
{
    m_mutex.lock();
    m_queue.push(value_);
    m_semaphore.post();
    m_mutex.unlock();
}

/**
 * @brief Pop element from the front of the queue
 * 
 * @tparam Container - same as was used in the constructor 
 * @param outparam_ pointer to value of element that was popped
 * 
 * @throw interprocess_exception on error
 */

template<typename Container>
void WaitableQueue<Container>::Pop(typename Container::reference outparam_)
{
    m_semaphore.wait();
    m_mutex.lock(); 
    outparam_ = m_queue.front();
    m_queue.pop();
    m_mutex.unlock();
}

/**
 * @brief Pop element from the front of the queue. If queue is empty, wait
 * until an element is pushed to queue.
 * 
 * @tparam Container - same as was used in the constructor 
 * @param outparam_ pointer to value of element that was popped
 * @param timeout_ duration to wait in seconds
 * @return true if an item was popped
 * @return false if reached timeout and item wasn't popped
 * 
 * @throw interprocess_exception on error
 */

template<typename Container>
bool WaitableQueue<Container>::Pop(typename Container::reference outparam_, size_t timeout_)
{
    if (m_semaphore.timed_wait(boost::posix_time::second_clock::universal_time() +
        boost::posix_time::seconds(timeout_)))
    {
        m_mutex.lock();
        outparam_ = m_queue.front();
        m_queue.pop();
        m_mutex.unlock();
        return true;
    }

    return false;
}

} // namespace ilrd

#endif // _ILRD_RD734_WAITABLE_QUEUE_HPP_



// Pop timeout - waiting to acquire mutex lock (not for queue resource)

// template<typename Container>
// bool WaitableQueue<Container>::Pop(typename Container::reference outparam_, size_t timeout_)
// {
//     bool ret = false;
    
//     if (m_mutex.timed_lock(boost::posix_time::second_clock::universal_time() +
//         boost::posix_time::seconds(timeout_)))
//     {
//         if (m_semaphore.try_wait())
//         {
//             outparam_ = m_queue.front();
//             // std::cout << "Pop: " << outparam_ << std::endl;
//             m_queue.pop();
//             ret = true;
//         }
//         m_mutex.unlock();
//     }

//     return ret;
// }