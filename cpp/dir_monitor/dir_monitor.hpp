#ifndef _ILRD_RD734_DIRMONITOR_HPP_
#define _ILRD_RD734_DIRMONITOR_HPP_

#include <string>

#include "reactor.hpp"
#include "command.hpp"
#include "event_handler.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    DirMonitor(std::string name_, CommandManager *cmd_manager, Reactor *reactor_); //non-explicit
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