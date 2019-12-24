#include <cstring> /* strcmp, strlen */

#include "string.hpp"

using namespace ilrd;

/**
 * @brief Construct a new String:: String object from str
 * 
 * @param str string of type const char*
 */

String::String(const char* str)
    : m_cstr(new char[strlen(str) + 1])
{
    strcpy(m_cstr, str);
}

/**
 * @brief Construct a new String:: String object by copying from another String object other_
 * 
 * @param other_ String object
 */

String::String(const String& other_)
    : m_cstr(new char[other_.Length() + 1]) 
{
    strcpy(m_cstr, other_.m_cstr);
}

/**
 * @brief Destroy the String:: String object
 * 
 */

String::~String()
{
    delete[] m_cstr;
    m_cstr = NULL;
}

/**
 * @brief Assign to a String object
 * 
 * @param other_ String object
 * @return String& reference to the newly assigned String object
 */

String& String::operator=(const String& other_)
{
    delete[] m_cstr;
    m_cstr = NULL;

    m_cstr = new char[other_.Length() + 1];
    strcpy(m_cstr, other_.m_cstr);

    return *this;
}

/**
 * @brief Get string length
 * 
 * @return size_t length of the string
 */

size_t String::Length() const
{
    return strlen(m_cstr);
}

/**
 * @brief Get pointer to string
 * 
 * @return const char* pointer of the string
 */

const char* String::CStr() const
{
    return m_cstr;
}

/**
 * @brief Check if two String objects are equal
 * 
 * @param lhs String object
 * @param rhs String object
 * @return true if equal
 * @return false if not
 */

bool ilrd::operator==(const String& lhs, const String& rhs)
{
    return (strcmp(lhs.CStr(), rhs.CStr()) == 0);
}

/**
 * @brief Check if LHS String object is less than RHS String object
 * 
 * @param lhs String object
 * @param rhs String object
 * @return true if less
 * @return false if not
 */

bool ilrd::operator<(const String& lhs, const String& rhs)
{
    return (strcmp(lhs.CStr(), rhs.CStr()) < 0);
}

/**
 * @brief Check if LHS String object is greater than RHS String object
 * 
 * @param lhs String object
 * @param rhs String object
 * @return true if greater
 * @return false if not
 */

bool ilrd::operator>(const String& lhs, const String& rhs)
{
    return (strcmp(lhs.CStr(), rhs.CStr()) > 0);
}

/**
 * @brief Creates an output String
 * 
 * @param os ostream object
 * @param str String object
 * @return std::ostream& of the String object 
 */

std::ostream& ilrd::operator<<(std::ostream& os, const String& str)
{
    os << str.CStr();

    return os;
}