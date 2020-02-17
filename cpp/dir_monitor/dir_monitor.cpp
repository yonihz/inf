#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#include "dir_monitor.hpp"
#include "logger.hpp"
#include "singleton.hpp"

namespace ilrd
{

DirMonitor::DirMonitor(std::string name_, Reactor *reactor_)
    : m_name(name_), m_fd(), m_reactor(reactor_) {}

DirMonitor::~DirMonitor()
{
    close(m_fd);
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

void DirMonitor::AddToReactor(Reactor::ReactorFunction func)
{
    m_reactor->AddFD(m_fd, Reactor::READ, func);
}

int DirMonitor::GetFD()
{
    return m_fd;
}

} // namespace ilrd