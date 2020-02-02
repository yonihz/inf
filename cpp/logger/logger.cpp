#include <iostream>

#include "logger.hpp"

namespace ilrd
{

Logger::Logger(Severity initialSeverity)
    : m_severity(initialSeverity), m_os(&std::cerr)
{
}

Logger::~Logger()
{
}

void Logger::Log(Logger::Severity msgSeverity, const char *msg)
{
    if (msgSeverity >= m_severity)
    {
        *m_os << msg;
    }
}

void Logger::Log(Logger::Severity msgSeverity, const std::string &msg)
{
    if (msgSeverity >= m_severity)
    {
        *m_os << msg;
    }
}

void Logger::SetOutputSeverity(Logger::Severity outputSeverity)
{
    m_severity = outputSeverity;
}

void Logger::SetOutput(std::ostream &output)
{
    m_os = &output;
}

} // namespace ilrd