#include "thread.hpp"

#include <errno.h>
#include <assert.h>

enum {SUCCESS = 0};

namespace ilrd
{

void CreateExceptionCheck(int status);
void JoinExceptionCheck(int status);
void DetachExceptionCheck(int status);
void TryJoinExceptionCheck(int status);

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
 * @throw ThreadException in case of unexpected error
 */

Thread::Thread(void*(*start_routine_)(void*), void* args_, Attr& attr_)
{   
    // get detach state from attr_ and set m_joinable
    int detach_state;
    pthread_attr_getdetachstate(&attr_.GetAttr(), &detach_state);
    m_joinable = (detach_state == PTHREAD_CREATE_JOINABLE);

    JoinExceptionCheck(pthread_create(&m_id, &attr_.GetAttr(), start_routine_, args_));
}

/**
 * @brief Destroy the Thread:: Thread object - cancels the thread
 * 
 */

Thread::~Thread()
{
    if (true == m_joinable)
    {
        Join();
    }
}
/**
 * @brief join with a terminated thread
 * 
 * @return void* thread return value
 * 
 * @throw NonJoinable in case of Thread is not joinable or another thread is already waiting to join with this Thread
 * @throw Deadlock in case of A deadlock  was  detected or Thread specifies the calling Thread
 * @throw ThreadException in case of unexpceted error
 */

void* Thread::Join()
{
    void *thread_return;
    
    JoinExceptionCheck(pthread_join(m_id, &thread_return));

    m_joinable = false; // used for check in dtor
    return thread_return;
}

/**
 * @brief try to join with a terminated thread
 * 
 * @return int - on success, these functions return 0; on error, they 
 * return an error number.
 */
int Thread::TryJoin(void *retval)
{   
    int status = pthread_tryjoin_np(m_id, &retval);
    TryJoinExceptionCheck(status);

    m_joinable = false; // used for check in dtor
    return status;
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
    DetachExceptionCheck(pthread_detach(m_id));

    m_joinable = false; // used for check in dtor
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
    pthread_attr_destroy(&GetAttr());
}

/**
 * @brief get current attributes of thread
 * 
 * @return pthread_attr_t* pointer to attributes structure
 */

pthread_attr_t &Thread::Attr::GetAttr()
{
    return attr;
}

size_t Thread::GetIDSelf()
{
    return pthread_self();
}

void CreateExceptionCheck(int status)
{
    switch(status)
    {
        case SUCCESS:
        {
            break;
        }
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
            throw ThreadException();
            break;
        }
    }    
}

void JoinExceptionCheck(int status)
{
    switch(status)
    {
        case SUCCESS:
        {
            break;
        }
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
        default:
        {
            throw ThreadException();
            break;
        }
    }
    
    assert(status != ESRCH); 
}

void DetachExceptionCheck(int status)
{
    switch(status)
    {
        case SUCCESS:
        {
            break;
        }    
        case EINVAL:
        {
            throw NonJoinable();
            break;
        }
        default:
        {
            throw ThreadException();
            break;
        }
    }

    assert(status != ESRCH);
}

void TryJoinExceptionCheck(int status)
{
    switch(status)
    {
        case SUCCESS:
        {
            break;
        }
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
        case EBUSY: // additional exception to the Join() exceptions
        {
            break;
        }
        default:
        {
            throw ThreadException();
            break;
        }
    }
    
    assert(status != ESRCH); 
}

} //namespace ilrd