#ifndef _ILRD_RD734_DIRMONITOR_HPP_
#define _ILRD_RD734_DIRMONITOR_HPP_

#include <string>

#include "reactor.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    DirMonitor(std::string name_, Reactor *reactor_); //non-explicit
    ~DirMonitor();
    
    int Init();
    void AddToReactor();
    int GetFD();

    void operator()(void);

private:
    std::string m_name;
    int m_fd;
    Reactor *m_reactor;
    EventHandler m_event_handler;
};

} // namespace ilrd

#endif // _ILRD_RD734_DIRMONITOR_HPP_