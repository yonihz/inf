#ifndef _ILRD_RD734_EVENT_HANDLER_HPP_
#define _ILRD_RD734_EVENT_HANDLER_HPP_

#include <sys/inotify.h>
#include <unistd.h>

#include "plugin_loader.hpp"
#include "logger_configurator.hpp"

namespace ilrd
{

class EventHandler
{
public:
    EventHandler(CommandManager *cmd_manager_);
    void SetFD(int fd_);

    void operator()(void);

private:
    static const size_t EVENT_SIZE = (sizeof (struct inotify_event));
    static const size_t BUFF_LEN = (1024 * (EVENT_SIZE + 16));
    int m_fd;
    PluginLoader m_plugin_loader;
    LoggerConfigurator m_logger_configurator;
};

} // namespace ilrd

#endif // _ILRD_RD734_EVENT_HANDLER_HPP_