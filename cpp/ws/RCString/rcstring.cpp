#include <cstring>

#include "rcstring.hpp"

namespace ilrd
{

RCString::RCString(const char* cStr_)
    : m_counter(), m_cStr()
{
}

RCString::RCString(const RCString& other_)
{

}

RCString::~RCString()
{

}

RCString& RCString::operator=(const RCString& other_)
{

}
    
// char operator[](size_t index_) const;
// CharProxy operator[](size_t index_);

const char* RCString::GetCStr() const
{

}

size_t RCString::Length() const
{

}

bool RCString::IsShared() const
{

}
 
bool operator<(const RCString& lhs, const RCString& rhs)
{

}

bool operator>(const RCString& lhs, const RCString& rhs)
{

}

bool operator==(const RCString& lhs, const RCString& rhs)
{

}

bool operator!=(const RCString& lhs, const RCString& rhs)
{

}

std::ostream& operator<<(std::ostream& os, const RCString& rcStr)
{
    
}

} // namespace ilrd