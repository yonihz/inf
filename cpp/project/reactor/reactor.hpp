#ifndef _ILRD_RD734_REACTOR_HPP_
#define _ILRD_RD734_REACTOR_HPP_

#include <map>

#include "fd_listener.hpp"
// #include "reactor_typedefs.hpp"

namespace ilrd
{
    
class Reactor
{
public:
    typedef boost::function<void(void)> Function;
    typedef FDListener::Mode FD_Mode;
    enum Mode
    {
        READ = FDListener::READ,
        WRITE = FDListener::WRITE,
        EXCEPT = FDListener::EXCEPT
    };

    //Reactor() = default
    //~Reactor() = default

    void Run();
    void Stop();
    void AddFD(int fd_, Mode mode_, Function func_);
    void RemoveFD(int fd_, Mode mode_);
    std::map<FDListener::ModeAndFD, Function> *GetFDToFuncs();

private:
    std::map<FDListener::ModeAndFD, Function> m_fdToFuncs;
    bool m_is_running; //new
};

} // namespace ilrd

#endif // !_ILRD_RD734_REACTOR_HPP_