#ifndef ILRD_RD734_COMMAND_HPP
#define ILRD_RD734_COMMAND_HPP

#include <netdb.h>

#include <boost/shared_ptr.hpp>

namespace ilrd
{

class Command
{
public:
    virtual ~Command() {}

    virtual void operator()(int sockfd, char *buffer, struct addrinfo *client_addrinfo, socklen_t *client_addrlen) = 0;
};

} //namespace ilrd

#endif // ILRD_RD734_COMMAND_HPP