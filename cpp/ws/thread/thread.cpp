#include "thread.hpp"

#include <errno.h>

namespace ilrd
{

Thread::Attr Thread::default_attr;

/**
 * @brief Construct a new Thread:: Thread object
 * 
 * @param start_routine_ new thread starts execution by invoking start_routine_
 * @param args_ passed as the sole argument of start_routine_
 * @param attr_ determines attributes for the new thread
 * 
 * @throw NoResource in case of Insufficient resources to create a thread
 * @throw InvalidAttr in case of Invalid settings in attr_
 * @throw NoPremission in case of No permission to set the parameters specified in attr_
 */

Thread::Thread(void*(*start_routine_)(void*), void* args_, Attr& attr_)
    : m_joinable(true)
{   
    switch(pthread_create(&m_id, attr_.GetAttr(), start_routine_, args_))
    {
        case EAGAIN:
        {
            throw NoResource();
            break;
        }
        case EINVAL:
        {
            throw InvalidAttr();
            break;
        }
        case EPERM:
        {
            throw NoPremission();
            break;
        }
        default:
        {
            break;
        }
    }
}

/**
 * @brief Destroy the Thread:: Thread object - cancels the thread
 * 
 */

Thread::~Thread()
{
    if (true == m_joinable)
    {
        pthread_cancel(m_id);
    }
}
/**
 * @brief join with a terminated thread
 * 
 * @return void* thread return value
 * 
 * @throw NonJoinable in case of Thread is not joinable or another thread is already waiting to join with this Thread
 * @throw Deadlock in case of A deadlock  was  detected or Thread specifies the calling Thread
 * @throw ThreadException in case of No thread with the ID thread could be found
 */

void* Thread::Join()
{
    void *thread_return;
    
    switch(pthread_join(m_id, &thread_return))
    {
        case EDEADLK:
        {
            throw Deadlock();
            break;
        }
        case EINVAL:
        {
            throw NonJoinable();
            break;
        }
        case ESRCH:
        {
            throw ThreadException();
            break;
        }
        default:
        {
            m_joinable = false;
            break;
        }
    }

    return thread_return;
}

/**
 * @brief detach a thread
 * 
 * @throw NonJoinable is case of Thread is not joinable or another thread is already waiting to join with this Thread
 * @throw ThreadException in case of No thread with the ID thread could be found
 * 
 */

void Thread::Detach()
{  
    switch(pthread_detach(m_id))
    {
        case EINVAL:
        {
            throw NonJoinable();
            break;
        }
        case ESRCH:
        {
            throw ThreadException();
            break;
        }
        default:
        {
            m_joinable = false;
            break;
        }
    }
}

/**
 * @brief get thread ID
 * 
 * @return size_t thread ID
 */

size_t Thread::GetID() const
{
    return m_id;
}

/**
 * @brief Construct a new Thread:: Attr:: Attr object with default attribute values
 * 
 */

Thread::Attr::Attr()
{
    pthread_attr_init(&attr);
}

/**
 * @brief Construct a new Thread:: Attr:: Attr object
 * 
 * @param attr_ pthread_attr_t attributes structure
 */

Thread::Attr::Attr(const pthread_attr_t& attr_)
    : attr(attr_)
{
}

/**
 * @brief Destroy the Thread:: Attr:: Attr object
 * 
 */

Thread::Attr::~Attr()
{
    pthread_attr_destroy(GetAttr());
}

/**
 * @brief get current attributes of thread
 * 
 * @return pthread_attr_t* pointer to attributes structure
 */

pthread_attr_t *Thread::Attr::GetAttr()
{
    return &attr;
}

} //namespace ilrd