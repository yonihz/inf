#ifndef ILRD_OL734_LOGGER_HPP
#define ILRD_OL734_LOGGER_HPP

#include <iosfwd>
#include <queue>

#include "thread.hpp"
#include "waitable_queue.hpp"

namespace ilrd
{

class Logger
{
public:
    enum Severity { DEBUG, INFO, WARNING, ERROR };

    explicit Logger(Severity initialSeverity = WARNING);
    ~Logger();

    void Log(Severity msgSeverity, const char *msg);
    void Log(Severity msgSeverity, const std::string &msg);

    void SetOutputSeverity(Severity outputSeverity);
    void SetOutput(std::ostream &output);

private:
    Severity m_severity;
    std::ostream *m_os;
    WaitableQueue< std::queue<std::string> > m_wqueue;
    size_t m_interval;
    Thread *m_thread;

    void *FlushQueue(void *thread_args_void);
};

extern Logger g_logger;

} // namespace ilrd

#endif // ILRD_OL734_LOGGER_HPP