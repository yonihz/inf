#ifndef _ILRD_RD743_THREAD_EXCEPT_HPP_
#define _ILRD_RD743_THREAD_EXCEPT_HPP_

#include <stdexcept> // runtime_error

namespace ilrd
{

class ThreadException : public std::runtime_error
{
public:
    ThreadException(const std::string& s_ = "Unexpected Thread Error")
        : runtime_error(s_) { }
};

class NoResource : public ThreadException
{
public:
    NoResource(const std::string& s_ =
        "Insufficient resources to create a thread")
        : ThreadException(s_) { }
};

class NoPremission : public ThreadException
{
public:
    NoPremission(const std::string& s_ =
        "No permission to set the parameters specified in attr_")
        : ThreadException(s_) { }
};

class InvalidAttr : public ThreadException
{
public:
    InvalidAttr(const std::string& s_ =
        "Invalid settings in attr_")
        : ThreadException(s_) { }
};

class NonJoinable : public ThreadException
{
public:
    NonJoinable(const std::string& s_ =
        "Thread is not joinable or another thread is already waiting to join with this Thread")
        : ThreadException(s_) { }
};

class Deadlock : public ThreadException
{
public:
    Deadlock(const std::string& s_ =
        "A  deadlock  was  detected or Thread specifies the calling Thread")
        : ThreadException(s_) { }
};

} //namespace ilrd

#endif // _ILRD_RD743_THREAD_EXCEPT_HPP_