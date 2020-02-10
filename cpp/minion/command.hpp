#ifndef ILRD_RD734_COMMAND_HPP
#define ILRD_RD734_COMMAND_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <boost/shared_ptr.hpp>

namespace ilrd
{

class CmdArgs
{
public:
    CmdArgs(int sockfd_, char *buffer_);

    int m_sockfd;
    char *m_buffer;
    struct addrinfo m_client_addrinfo;
    socklen_t m_client_addrlen;
};

class Command
{
public:
    virtual void operator()(CmdArgs &args);
};

class ReadRequestCmd : public Command
{
public:
    void operator()(CmdArgs &args);
};

class WriteRequestCmd : public Command
{
public:
    void operator()(CmdArgs &args);
};

boost::shared_ptr<Command> CreateReadRequestCmd(void)
{
    boost::shared_ptr<Command> command(new ReadRequestCmd());
    return command;
}

boost::shared_ptr<Command> CreateWriteRequestCmd(void)
{
    boost::shared_ptr<Command> command(new WriteRequestCmd());
    return command;
}

}

#endif // ILRD_RD734_COMMAND_HPP