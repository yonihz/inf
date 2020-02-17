#include "boost/lexical_cast.hpp" 
using boost::lexical_cast;

#include "event_handler.hpp"
#include "logger.hpp"
#include "singleton.hpp"

namespace ilrd
{

EventHandler::EventHandler(CommandManager *cmd_manager_)
    : m_fd(), m_plugin_loader(cmd_manager_), m_logger_configurator() {}
    
void EventHandler::operator()(void)
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
            
            if (name == "logger.ini")
            {
                m_logger_configurator();
            }
            else
            {
                m_plugin_loader(name);
            }
        }

        i += EVENT_SIZE + event->len;
    }
}

void EventHandler::SetFD(int fd_)
{
    m_fd = fd_;
}

} // namespace ilrd