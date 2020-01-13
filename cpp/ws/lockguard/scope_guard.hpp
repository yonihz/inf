#ifndef _ILRD_RD743_SCOPE_GUARD_HPP_
#define _ILRD_RD743_SCOPE_GUARD_HPP_

namespace ilrd
{

template<typename Resource, void(Resource::*Acquire)(), void(Resource::*Release)()>
class ScopeGuard
{    
public:
    explicit ScopeGuard(Resource& resource_);
    ~ScopeGuard();

private:
    Resource& m_resource;

    ScopeGuard(const ScopeGuard&);
    const ScopeGuard& operator=(const ScopeGuard&);
};

} //namespace ilrd

#endif // _ILRD_RD743_SCOPE_GUARD_HPP_