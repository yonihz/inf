#include <iostream>

#include "logger.hpp"

namespace ilrd
{

Logger::Logger(Severity initialSeverity)
    : m_sseverity(initialSeverity), m_soutput(&std::cerr), m_wqueue(), m_thread(), m_is_alive(true)
{
    m_thread = new Thread(WriteToStream, (void*)this);
}

Logger::~Logger()
{
    m_is_alive = false;
    m_thread->Join();
    delete m_thread;
}

void Logger::Log(Logger::Severity msgSeverity, const char *msg)
{
    if (msgSeverity >= GetOutputSeverity())
    {
        m_wqueue.Push(msg);
    }
}

void Logger::Log(Logger::Severity msgSeverity, const std::string &msg)
{
    if (msgSeverity >= GetOutputSeverity())
    {
        m_wqueue.Push(msg);
    }
}

void Logger::SetOutputSeverity(Logger::Severity outputSeverity)
{
    m_sseverity.SetSafeSeverity(outputSeverity);
}

Logger::Severity Logger::GetOutputSeverity()
{
    return m_sseverity.GetSafeSeverity();
}

void Logger::IncOutputSeverity()
{
    m_sseverity.IncSafeSeverity();
}

void Logger::DecOutputSeverity()
{
    m_sseverity.DecSafeSeverity();
}

void Logger::SetOutput(std::ostream &output)
{
    m_soutput.SetSafeOutput(&output);
}

std::ostream *Logger::GetOutput()
{
    return m_soutput.GetSafeOutput();
}

void *Logger::WriteToStream(void *logger_void)
{
    Logger &logger = *(Logger*)logger_void;
    std::string outparam_str;

    while(logger.m_is_alive)
    {
        if (logger.m_wqueue.Pop(outparam_str, 5) == true)
        {
            *(logger.GetOutput()) << outparam_str;
        }
    }

    return NULL;
}

Logger::SafeSeverity::SafeSeverity(Severity initialSeverity)
    : m_severity(initialSeverity), m_mutex() {}

void Logger::SafeSeverity::SetSafeSeverity(Severity outputSeverity)
{
    m_mutex.lock();
    m_severity = outputSeverity;
    m_mutex.unlock();
}

Logger::Severity Logger::SafeSeverity::GetSafeSeverity()
{
    Logger::Severity ret_sev;
    m_mutex.lock();
    ret_sev = m_severity;
    m_mutex.unlock();

    return ret_sev;    
}

void Logger::SafeSeverity::IncSafeSeverity()
{
    m_mutex.lock();
    switch(m_severity)
    {
        case Logger::DEBUG:
        {
            break;
        }
        case Logger::INFO:
        {
            m_severity = Logger::DEBUG;
            break;
        }
        case Logger::WARNING:
        {
            m_severity = Logger::INFO;
            break;
        }
        case Logger::ERROR:
        {
            m_severity = Logger::WARNING;
            break;
        }
        default:
        {
            break;
        }
    }
    m_mutex.unlock();
}

void Logger::SafeSeverity::DecSafeSeverity()
{
    m_mutex.lock();
    switch(m_severity)
    {
        case Logger::DEBUG:
        {
            m_severity = Logger::INFO;
            break;
        }
        case Logger::INFO:
        {
            m_severity = Logger::WARNING;
            break;
        }
        case Logger::WARNING:
        {
            m_severity = Logger::ERROR;
            break;
        }
        case Logger::ERROR:
        {
            break;
        }
        default:
        {
            break;
        }
    }
    m_mutex.unlock();
}

Logger::SafeOutput::SafeOutput(std::ostream *os)
    : m_os(os) {}

void Logger::SafeOutput::SetSafeOutput(std::ostream *os)
{
    m_mutex.lock();
    m_os = os;
    m_mutex.unlock();
}

std::ostream *Logger::SafeOutput::GetSafeOutput()
{
    std::ostream *ret_os;
    m_mutex.lock();
    ret_os = m_os;
    m_mutex.unlock();

    return ret_os;
}

} // namespace ilrd