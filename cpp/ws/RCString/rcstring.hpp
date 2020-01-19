#ifndef _ILRD_RD734_RCSTRING_HPP_
#define _ILRD_RD734_RCSTRING_HPP_

#include <iostream> // ostream
#include <cstddef>  // size_t


namespace ilrd
{

class RCString
{
public:
    RCString(const char* cStr_ = ""); // non explicit
    RCString(const RCString& other_);    
    ~RCString();
    RCString& operator=(const RCString& other_);
    
    // char operator[](size_t index_) const;
    // CharProxy operator[](size_t index_);

    const char* GetCStr() const;
    size_t Length() const;
    bool IsShared() const;

private:
    size_t* m_counter;
    char* m_cStr;

    void CleanupLast();
};
 
bool operator<(const RCString& lhs, const RCString& rhs);
bool operator>(const RCString& lhs, const RCString& rhs);
bool operator==(const RCString& lhs, const RCString& rhs);
bool operator!=(const RCString& lhs, const RCString& rhs);
std::ostream& operator<<(std::ostream& os, const RCString& rcStr);

} // namespace ilrd

#endif // _ILRD_RD734_RCSTRING_HPP_