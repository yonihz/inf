#ifndef _ILRD_RD743_SCOPE_GUARD_HPP_
#define _ILRD_RD743_SCOPE_GUARD_HPP_

#include <boost/core/noncopyable.hpp>

namespace ilrd
{

template<typename Resource, void(Resource::*Acquire)(), void(Resource::*Release)()>
class ScopeGuard : private boost::noncopyable
{    
public:
    explicit ScopeGuard(Resource& resource_);
    ~ScopeGuard();

private:
    Resource& m_resource;

    ScopeGuard(const ScopeGuard&);
    const ScopeGuard& operator=(const ScopeGuard&);
};

template<typename Resource, void(Resource::*Acquire)(), void(Resource::*Release)()>
ScopeGuard<Resource, Acquire, Release>::ScopeGuard(Resource& resource_)
    : m_resource(resource_)
{
    try
    {
        (m_resource.*Acquire)();
    }
    catch(...)
    {
        std::cerr << "ScopeGuard error in Acquire()" << '\n';
    }  
}

template<typename Resource, void(Resource::*Acquire)(), void(Resource::*Release)()>
ScopeGuard<Resource, Acquire, Release>::~ScopeGuard()
{
    try
    {
        (m_resource.*Release)();
    }
    catch(const std::exception& e)
    {
        std::cerr << "ScopeGuard error in Release()" << '\n';
    }   
}

} //namespace ilrd

#endif // _ILRD_RD743_SCOPE_GUARD_HPP_