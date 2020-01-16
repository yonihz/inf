#include "waitable_queue.hpp"

namespace ilrd
{

template<typename Container>
WaitableQueue<Container>::WaitableQueue()
{
}

template<typename Container>
WaitableQueue<Container>::~WaitableQueue()
{
}

template<typename Container>
void WaitableQueue<Container>::Push(typename Container::const_reference value_)
{
    m_mutex.lock();
    m_queue.push(value_);
    m_semaphore.post();
    m_mutex.unlock();
}

template<typename Container>
void WaitableQueue<Container>::Pop(typename Container::reference outparam_)
{
    m_semaphore.wait())
    m_mutex.lock(); 
    outparam_ = m_queue.front();
    m_queue.pop();
    m_mutex.unlock();
}

template<typename Container>
bool WaitableQueue<Container>::Pop(typename Container::reference outparam_, const boost::posix_time::ptime& timeout_)
{
    bool ret = false;
    
    if (m_mutex.timed_lock(timeout_))
    {
        if (m_semaphore.try_wait())
        {
            outparam_ = m_queue.front();
            m_queue.pop();
            ret = true;
        }

        m_mutex.unlock();
    }

    return ret;
}

} // namespace ilrd