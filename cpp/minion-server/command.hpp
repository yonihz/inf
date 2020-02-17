#ifndef ILRD_RD734_COMMAND_HPP
#define ILRD_RD734_COMMAND_HPP

#include <netdb.h>

#include <boost/shared_ptr.hpp>

#include "factory.hpp"
#include "reactor.hpp"

namespace ilrd
{

class Command
{
public:
    virtual ~Command() {}

    virtual void operator()(char *buffer) = 0;

    enum {SUCCESS = 0, FAIL = 1};

    const static size_t BLOCK_SIZE = 4096;
    const static size_t SEND_BLOCK_IDX_BYTE = 9;
    const static size_t SEND_DATA_BYTE = 17;
    const static size_t REPLY_STATUS_BYTE = 9;
    const static size_t REPLY_DATA_BYTE = 10;
};

class CommandManager
{
public:
    CommandManager(Reactor *reactor_);

    void RunCommand(char c_, char *buffer_);
    void AddCommand(char c_, boost::shared_ptr<Command>(*creator_)(void));

    void operator()(void);
private:
    Reactor *m_reactor;
    Factory<boost::shared_ptr<Command>, char, void, boost::shared_ptr<Command>(*)(void)> m_factory;
};

} //namespace ilrd

#endif // ILRD_RD734_COMMAND_HPP