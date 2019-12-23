#include <cstring> /* strcmp, strlen */

#include "string.hpp"

using namespace ilrd;

String::String(const char* str)
    : m_cstr(new char[strlen(str) + 1])
{
    strcpy(m_cstr, str);
}

String::String(const String& other_)
    : m_cstr(new char[other_.Length() + 1]) 
{
    strcpy(m_cstr, other_.m_cstr);
}

String::~String()
{
    delete[] m_cstr;
}

String& String::operator=(const String& other_)
{
    delete[] m_cstr;
    m_cstr = NULL;

    m_cstr = new char[Length() + 1];
    strcpy(m_cstr, other_.m_cstr);

    return *this;
}

size_t String::Length() const
{
    return strlen(m_cstr);
}

const char* String::CStr() const
{
    return m_cstr;
}

bool ilrd::operator==(const String& lhs, const String& rhs)
{
    return (strcmp(lhs.CStr(), rhs.CStr()) == 0);
}

bool ilrd::operator<(const String& lhs, const String& rhs)
{
    return (strcmp(lhs.CStr(), rhs.CStr()) < 0);
}

bool ilrd::operator>(const String& lhs, const String& rhs)
{
    return (strcmp(lhs.CStr(), rhs.CStr()) > 0);
}

std::ostream& ilrd::operator<<(std::ostream& os, const String& str)
{
    os << str.CStr();

    return os;
}