#ifndef _ILRD_RD743_LOCK_GUARD_HPP_
#define _ILRD_RD743_LOCK_GUARD_HPP_

namespace ilrd
{

template<typename Lockable>
class LockGuard
{    
public:
    explicit LockGuard(Lockable& lockable_);
    ~LockGuard();

private:
    Lockable& m_lockable;

    LockGuard(const LockGuard&);
    const LockGuard& operator=(const LockGuard&);
};

} //namespace ilrd

#endif // _ILRD_RD743_LOCK_GUARD_HPP_