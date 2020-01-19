#include <cstring>

#include "rcstring.hpp"

namespace ilrd
{

RCString::RCString(const char* cStr_)
    : m_counter(), m_cStr()
{
    void *alloc = new char[strlen(cStr_) + 1 + sizeof(size_t)];
    m_counter = static_cast<size_t*>(alloc);
    *m_counter = 1;
    m_cStr = static_cast<char*>(alloc) + sizeof(size_t);
    strcpy(m_cStr, cStr_);
}

RCString::RCString(const RCString& other_)
    : m_counter(other_.m_counter), m_cStr(other_.m_cStr)
{
    ++(*m_counter);
}

RCString::~RCString()
{
    CleanUpIfLast();
}

RCString& RCString::operator=(const RCString& other_)
{
    if (m_cStr == other_.m_cStr)
    {
        return *this;
    }

    CleanUpIfLast();

    m_cStr = other_.m_cStr;
    m_counter = other_.m_counter;
    ++(*m_counter);
    return *this;    
}

inline void RCString::CleanUpIfLast()
{
    if (IsShared())
    {
        --(*m_counter);
    }
    else
    {
        delete[] reinterpret_cast<char*>(m_counter);
    }
}

// char RCString::operator[](size_t index_) const
// {
//     return m_cStr[index_];
// }

RCString::CharProxy RCString::operator[](size_t index_)
{

}

const char* RCString::GetCStr() const
{
    return m_cStr;
}

size_t RCString::Length() const
{
    return strlen(m_cStr);
}

bool RCString::IsShared() const
{
    return (*m_counter != 1);
}
 
bool operator<(const RCString& lhs, const RCString& rhs)
{
    return (0 > strcmp(lhs.GetCStr(), rhs.GetCStr()));
}

bool operator>(const RCString& lhs, const RCString& rhs)
{
    return (0 < strcmp(lhs.GetCStr(), rhs.GetCStr()));
}

bool operator==(const RCString& lhs, const RCString& rhs)
{
    return (0 == strcmp(lhs.GetCStr(), rhs.GetCStr()));
}

bool operator!=(const RCString& lhs, const RCString& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const RCString& rcStr)
{
    return os << rcStr.GetCStr();
}

RCString::CharProxy::CharProxy(RCString &str_, size_t idx_)
{

}

RCString::CharProxy::~CharProxy()
{

}

char RCString::CharProxy::operator=(char c)
{

}

RCString::CharProxy::operator char() const
{
    return m_org->GetCStr()[m_idx];
}

} // namespace ilrd