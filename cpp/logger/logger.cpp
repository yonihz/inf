#include <iostream>

#include "logger.hpp"

namespace ilrd
{

struct ThreadArgs {
    WaitableQueue< std::queue<std::string> > *wqueue;
    std::ostream *os;
    size_t *interval;
};

Logger g_logger(Logger::WARNING);

Logger::Logger(Severity initialSeverity)
    : m_severity(initialSeverity), m_os(&std::cerr), m_wqueue(), m_interval(), m_thread()
{
    ThreadArgs *thread_args = new ThreadArgs;
    thread_args->wqueue = &m_wqueue;
    thread_args->os = m_os;
    thread_args->interval = &m_interval;

    m_thread = new Thread(FlushQueue, (void*)&thread_args);
}

Logger::~Logger()
{
}

void Logger::Log(Logger::Severity msgSeverity, const char *msg)
{
    if (msgSeverity >= m_severity)
    {
        std::string str(msg);
        m_wqueue.Push(str);
    }

    // if (msgSeverity >= m_severity)
    // {
    //     *m_os << msg;
    // }
}

void Logger::Log(Logger::Severity msgSeverity, const std::string &msg)
{
    if (msgSeverity >= m_severity)
    {
        m_wqueue.Push(msg);
    }

    // if (msgSeverity >= m_severity)
    // {
    //     *m_os << msg;
    // }
}

void Logger::SetOutputSeverity(Logger::Severity outputSeverity)
{
    m_severity = outputSeverity;
}

void Logger::SetOutput(std::ostream &output)
{
    m_os = &output;
}

void *Logger::FlushQueue(void *thread_args_void)
{
    ThreadArgs* thread_args = static_cast<ThreadArgs*>(thread_args_void);

    WaitableQueue< std::queue<std::string> > *wqueue = thread_args->wqueue;
    std::ostream *os = thread_args->os;
    size_t *interval = thread_args->interval;

    delete thread_args_void;

    // while(1)
    // {
    //     while(1) // change to waitinterval
    //     {
    //         while(pop == true)
    //     }
    // }
}

} // namespace ilrd