#include "thread.hpp"

#include <errno.h>

namespace ilrd
{

Thread::Attr Thread::default_attr;

Thread::Thread(void*(*start_routine_)(void*), void* args_, Attr& attr_)
    : m_joinable(true)
{
    int status = 0;
    status = pthread_create(&m_id, attr_.GetAttr(), start_routine_, args_);
    
    switch(status)
    {
        case EAGAIN:
        {
            throw ilrd::NoResource();
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

Thread::~Thread()
{
    if (true == m_joinable)
    {
        Join();
    }
}

void* Thread::Join()
{
    void* thread_return;

    int status = 0;
    status = pthread_join(m_id, &thread_return);
    
    switch(status)
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

void Thread::Detach()
{
    int status = 0;
    status = pthread_detach(m_id);
    
    switch(status)
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

size_t Thread::GetID() const
{
    return m_id;
}

Thread::Attr::Attr()
{
    pthread_setattr_default_np(&attr);
}

Thread::Attr::Attr(const pthread_attr_t& attr_)
    : attr(attr_)
{
}

Thread::Attr::~Attr()
{
}

pthread_attr_t *Thread::Attr::GetAttr()
{
    return &attr;
}

} //namespace ilrd