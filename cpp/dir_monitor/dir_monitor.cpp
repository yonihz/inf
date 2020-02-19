#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast;

#include "dir_monitor.hpp"
#include "logger.hpp"
#include "singleton.hpp"

namespace ilrd
{

DirMonitor::DirMonitor(std::string name_, Reactor *reactor_, Dispatcher<std::string> *dispatcher_)
    : m_name(name_), m_fd(), m_reactor(reactor_), m_dispatcher(dispatcher_) {}

DirMonitor::~DirMonitor()
{
    // close(m_fd);
}

int DirMonitor::Init()
{
    Logger &logger = *(Singleton<Logger>::Instance());
    int wd;

    m_fd = inotify_init1(IN_NONBLOCK);

    if (m_fd == -1)
    {
        logger.Log(Logger::ERROR, "inotify_init1: " + std::string(strerror(errno)) + "\n");
        return -1;
    }

    wd = inotify_add_watch(m_fd, m_name.c_str(), IN_CREATE);

    if (wd == -1)
    {
        logger.Log(Logger::ERROR, "wd: " + std::string(strerror(errno)) + "\n");
        return -1;
    }

    return m_fd;
}

void DirMonitor::AddToReactor()
{
    m_reactor->AddFD(m_fd, Reactor::READ, *this);
}

void DirMonitor::operator()(void)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    char buff[BUFF_LEN];
    int len;

    len = read(m_fd, buff, BUFF_LEN);

    if ((-1 == len) && (errno != EAGAIN)) 
    {
        logger.Log(Logger::ERROR, "read: " + std::string(strerror(errno)) + "\n");
        return;
    }
    else if (0 == len)
    {
        logger.Log(Logger::ERROR, "read: len = 0 (buffer might be too small)\n");
        return;
    }

    int i = 0;
    while (i < len) 
    {
        struct inotify_event *event;

        event = (struct inotify_event *)&buff[i];

        // logger.Log(Logger::DEBUG, 
        //     "event: wd = " + lexical_cast<std::string>(event->wd) +
        //     " mask = " + lexical_cast<std::string>(event->mask) + 
        //     " cookie = " + lexical_cast<std::string>(event->cookie) +
        //     " len = " + lexical_cast<std::string>(event->len) + "\n");

        if (0 != event->len)
        {
            std::string name = lexical_cast<std::string>((char*)event->name);
            logger.Log(Logger::DEBUG, 
                "event: name = " + name + "\n");
            
            sleep(1);
            m_dispatcher->NotifyAll(name);
        }

        i += EVENT_SIZE + event->len;
    }
}

} // namespace ilrd