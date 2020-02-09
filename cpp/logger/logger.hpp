#ifndef ILRD_OL734_LOGGER_HPP
#define ILRD_OL734_LOGGER_HPP

#include <iosfwd>
#include <queue>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/core/noncopyable.hpp>

#include "thread.hpp"
#include "waitable_queue.hpp"

namespace ilrd
{

class Logger
{
    class SafeSeverity;
    class SafeOutput;
public:
    enum Severity { DEBUG, INFO, WARNING, ERROR };

    explicit Logger(Severity initialSeverity = DEBUG);
    ~Logger();

    void Log(Severity msgSeverity, const char *msg);
    void Log(Severity msgSeverity, const std::string &msg);

    void SetOutputSeverity(Severity outputSeverity);
    Severity GetOutputSeverity();
    void IncOutputSeverity();
    void DecOutputSeverity();

    void SetOutput(std::ostream &output);
    std::ostream *GetOutput();

private:
    class SafeSeverity : private boost::noncopyable
    {
    public:
        SafeSeverity(Severity initialSeverity);
        void SetSafeSeverity(Severity outputSeverity);
        Severity GetSafeSeverity();
        void IncSafeSeverity();
        void DecSafeSeverity();

    private:
        Severity m_severity;
        boost::interprocess::interprocess_mutex m_mutex;
    };

    class SafeOutput
    {
     public:
        SafeOutput(std::ostream *os);
        void SetSafeOutput(std::ostream *os);
        std::ostream *GetSafeOutput();

    private:
        std::ostream *m_os;
        boost::interprocess::interprocess_mutex m_mutex;       
    };

    SafeSeverity m_sseverity;
    SafeOutput m_soutput;
    WaitableQueue< std::queue<std::string> > m_wqueue;
    Thread *m_thread;
    bool m_is_alive;

    static void *WriteToStream(void *logger_void);
};

} // namespace ilrd

#endif // ILRD_OL734_LOGGER_HPP