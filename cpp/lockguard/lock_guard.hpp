// compile command:
// gd98 lock_guard_test.cpp ../thread/thread.cpp -I../thread/ -pthread

#ifndef _ILRD_RD743_LOCK_GUARD_HPP_
#define _ILRD_RD743_LOCK_GUARD_HPP_

#include <boost/core/noncopyable.hpp>

namespace ilrd
{

template<typename Lockable>
class LockGuard : private boost::noncopyable
{    
public:
    explicit LockGuard(Lockable& lockable_);
    ~LockGuard();

private:
    Lockable& m_lockable;

    LockGuard(const LockGuard&);
    const LockGuard& operator=(const LockGuard&);
};

template<typename Lockable>
LockGuard<Lockable>::LockGuard(Lockable& lockable_)
    : m_lockable(lockable_)
{
    try
    {
        m_lockable.lock();
    }
    catch(...)
    {
        std::cerr << "LockGuard error in lock()" << '\n';
    }
}

template<typename Lockable>
LockGuard<Lockable>::~LockGuard()
{
    try
    {
        m_lockable.unlock();
    }
    catch(...)
    {
        std::cerr << "LockGuard error in unlock()" << '\n';
    }
}

} //namespace ilrd

#endif // _ILRD_RD743_LOCK_GUARD_HPP_