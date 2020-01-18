#ifndef _ILRD_RD743_THREAD_HPP_
#define _ILRD_RD743_THREAD_HPP_

#include <pthread.h> // p_thread
	
#include "thread_exception.hpp"

namespace ilrd
{

class Thread
{    
public:
    class Attr;

    Thread(void*(*start_routine_)(void*), void* args_, Attr& attr_ = default_attr);
    ~Thread();

    void* Join();
    void Detach();
    size_t GetID() const;
    static size_t GetIDSelf();

    //static function get self id

private:
    pthread_t m_id;
    bool m_joinable;
    
    static Attr default_attr;

    Thread(const Thread&);
    const Thread& operator=(const Thread&);

public:
    class Attr
    {
    public:
        Attr();
        Attr(const pthread_attr_t& attr_);
        ~Attr();

        pthread_attr_t &GetAttr();

    private:
        pthread_attr_t attr;
    };
};

} //namespace ilrd

#endif // _ILRD_RD743_THREAD_HPP_