#ifndef _ILRD_RD734_REACTOR_HPP_
#define _ILRD_RD734_REACTOR_HPP_

#include <map>

#include "fd_listener.hpp"
#include "reactor_typedefs.hpp"

namespace ilrd
{
    
class Reactor
{
public:
    typedef boost::function<void(void)> Function;
    typedef FDListener::Mode FD_Mode;
    enum Mode
    {
        READ = FD_Mode::READ,
        WRITE = FD_Mode::WRITE,
        EXCEPT = FD_Mode::EXCEPT
    };

    //Reactor() = default
    //~Reactor() = default

    void Run();
    void Stop();
    void AddFD(int fd_, Mode mode_, Function func_);
    void RemoveFD(int fd_, Mode mode_);

private:
    std::map<FDListener::ModeAndFD, Function> m_fdToFuncs;
};

} // namespace ilrd

#endif // !_ILRD_RD734_REACTOR_HPP_