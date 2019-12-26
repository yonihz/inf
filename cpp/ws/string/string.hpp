#ifndef _ILRD_RD743_STRING_HPP_
#define _ILRD_RD743_STRING_HPP_

#include <cstdlib> // size_t
#include <iostream> // std::ostream

namespace ilrd
{
class String
{
public:
    String(const char* str = ""); // non-explicit
    String(const String& other_);
    ~String();

    String& operator=(const String& other_);

    size_t Length() const;
    const char* CStr() const;

private:
    char* m_cstr;
};

bool operator==(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& os, const String& str);
}

#endif // _ILRD_RD743_STRING_HPP_