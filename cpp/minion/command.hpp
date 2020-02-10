#ifndef ILRD_RD734_COMMAND_HPP
#define ILRD_RD734_COMMAND_HPP

#include <netdb.h>

#include <boost/shared_ptr.hpp>

namespace ilrd
{

class CmdArgs
{
public:
    CmdArgs(int sockfd_, char *buffer_);

    int m_sockfd;
    char *m_buffer;
    addrinfo m_client_addrinfo;
    socklen_t m_client_addrlen;
};

class Command
{
public:
    explicit Command(CmdArgs &args_);
    virtual ~Command() {}

    virtual void operator()() = 0;
    CmdArgs &m_args;
};

class ReadRequestCmd : public Command
{
public:
    ReadRequestCmd(CmdArgs &args_);

    void operator()(void);
};

class WriteRequestCmd : public Command
{
public:
    WriteRequestCmd(CmdArgs &args_);

    void operator()(void);
};

boost::shared_ptr<Command> CreateReadRequestCmd(CmdArgs &args);
boost::shared_ptr<Command> CreateWriteRequestCmd(CmdArgs &args);

}

#endif // ILRD_RD734_COMMAND_HPP