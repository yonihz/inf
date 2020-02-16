#ifndef _ILRD_RD734_DIRMONITOR_HPP_
#define _ILRD_RD734_DIRMONITOR_HPP_

#include "reactor.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    DirMonitor(std::string path, Reactor *reactor_); //non-explicit
    ~DirMonitor();

private:
    std::string m_path;
    Reactor *m_reactor;
};

} // namespace ilrd

#endif // _ILRD_RD734_DIRMONITOR_HPP_