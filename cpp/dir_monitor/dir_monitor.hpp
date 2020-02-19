#ifndef _ILRD_RD734_DIRMONITOR_HPP_
#define _ILRD_RD734_DIRMONITOR_HPP_

#include <string>
#include <sys/inotify.h>

#include "reactor.hpp"
#include "command.hpp"
#include "dispatcher.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    DirMonitor(std::string name_, Reactor *reactor_, Dispatcher<std::string> *dispatcher_); //non-explicit
    ~DirMonitor();
    
    int Init();
    void AddToReactor();

    void operator()(void);

private:
    static const size_t EVENT_SIZE = (sizeof (struct inotify_event));
    static const size_t BUFF_LEN = (1024 * (EVENT_SIZE + 16));
    std::string m_name;
    int m_fd;
    Reactor *m_reactor;
    Dispatcher<std::string> *m_dispatcher;
};

} // namespace ilrd

#endif // _ILRD_RD734_DIRMONITOR_HPP_