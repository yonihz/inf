#include <cstring>  // strlen, strcmp, strcpy

#include "rcstring.hpp"

namespace ilrd
{

inline void AllocStr(size_t **m_counter, char **m_cStr, const char *cStr_)
{
    void *alloc = new char[strlen(cStr_) + 1 + sizeof(size_t)];
    *m_counter = static_cast<size_t*>(alloc);
    **m_counter = 1;
    *m_cStr = static_cast<char*>(alloc) + sizeof(size_t);
    strcpy(*m_cStr, cStr_);
}

/**
 * @brief Construct a new RCString::RCString object
 * An RCString object references to the same string when copied, so no new
 * memory allocation is made
 * @param cStr_ a C-style string
 * @throw bad_alloc in case of allocation error
 */

RCString::RCString(const char* cStr_)
    : m_counter(), m_cStr()
{
    AllocStr(&m_counter, &m_cStr, cStr_);
}

/**
 * @brief Construct a new RCString::RCString object
 * This Ctor references to the same string as other_
 * @param other_ another RCString object
 */

RCString::RCString(const RCString& other_)
    : m_counter(other_.m_counter), m_cStr(other_.m_cStr)
{
    ++(*m_counter);
}

/**
 * @brief Destroy the RCString::RCString object
 * Delete allocated memory for string if its the last reference
 */

RCString::~RCString()
{
    CleanUpIfLast();
}

/**
 * @brief operator= references to the string referenced by other_ and destroys
 * the original string if it was its last reference
 * 
 * @param other_ another RCString object
 * @return RCString& of other_
 */

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

/**
 * @brief Deletes the referenced string if its unique
 * 
 */

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

/**
 * @brief operator[] returns a CharProxy object that can be modified
 * 
 * @param index_ in the string
 * @return RCString::CharProxy 
 */

RCString::CharProxy RCString::operator[](size_t index_)
{
    return CharProxy(*this, index_);
}

/**
 * @brief returns the C-style string referenced by the object
 * 
 * @return const char* 
 */

const char* RCString::GetCStr() const
{
    return m_cStr;
}

/**
 * @brief returns the length of the string
 * 
 * @return size_t 
 */

size_t RCString::Length() const
{
    return strlen(m_cStr);
}

/**
 * @brief returns whether string is not unique
 * 
 * @return true if not unique (referenced more than once)
 * @return false if unique (referenced once)
 */

bool RCString::IsShared() const
{
    return (*m_counter != 1);
}

/**
 * @brief return whether lhs < rhs
 * 
 * @param lhs 
 * @param rhs 
 * @return true 
 * @return false 
 */

bool operator<(const RCString& lhs, const RCString& rhs)
{
    return (0 > strcmp(lhs.GetCStr(), rhs.GetCStr()));
}

/**
 * @brief return whether lhs > rhs
 * 
 * @param lhs 
 * @param rhs 
 * @return true 
 * @return false 
 */

bool operator>(const RCString& lhs, const RCString& rhs)
{
    return (0 < strcmp(lhs.GetCStr(), rhs.GetCStr()));
}

/**
 * @brief return whether lhs == rhs
 * 
 * @param lhs 
 * @param rhs 
 * @return true 
 * @return false 
 */

bool operator==(const RCString& lhs, const RCString& rhs)
{
    return (0 == strcmp(lhs.GetCStr(), rhs.GetCStr()));
}

/**
 * @brief return whether lhs != rhs
 * 
 * @param lhs 
 * @param rhs 
 * @return true 
 * @return false 
 */

bool operator!=(const RCString& lhs, const RCString& rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief overloads operator<< with RCString object
 * 
 * @param os 
 * @param rcStr 
 * @return std::ostream& 
 */

std::ostream& operator<<(std::ostream& os, const RCString& rcStr)
{
    return os << rcStr.GetCStr();
}

/**
 * @brief Construct a new RCString::CharProxy::CharProxy object
 * This object keeps a reference to an RCString instance 
 * and index in the string
 * 
 * @param str_ 
 * @param idx_ 
 */

RCString::CharProxy::CharProxy(RCString &str_, size_t idx_)
    : m_org(&str_), m_idx(idx_)
{

}

/**
 * @brief Destroy the RCString::CharProxy::CharProxy object
 * 
 */

RCString::CharProxy::~CharProxy()
{
}

/**
 * @brief operator= assigns char c at the index position of the string kept
 * in the CharProxy object and creates a new reference to the modified string
 * 
 * @param c 
 * @return char 
 */

char RCString::CharProxy::operator=(char c)
{
    // if assigned the same char do nothing
    if (c == m_org->GetCStr()[m_idx])
    {
        return  m_org->GetCStr()[m_idx];
    }
    
    m_org->SetChar(m_idx, c);
    
    return m_org->GetCStr()[m_idx];
}

RCString::CharProxy& RCString::CharProxy::operator=(CharProxy cp)
{
    m_org->SetChar(m_idx, cp.m_org->GetCStr()[cp.m_idx]);
    return *this;
}

/**
 * @brief conversion to char
 * 
 * @return char 
 */

RCString::CharProxy::operator char() const
{
    return m_org->GetCStr()[m_idx];
}

/**
 * @brief set char of string at index idx_ to c
 * 
 * @param idx_ 
 * @param c 
 */

void RCString::SetChar(size_t idx_, char c)
{
    // if RCString is not unique create a new string and counter
    if (IsShared())
    {
        const char *org_cStr = GetCStr();
        --(*m_counter);
        AllocStr(&m_counter, &m_cStr, org_cStr);
    }

    m_cStr[idx_] = c;
}

} // namespace ilrd