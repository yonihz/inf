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

    virtual void operator()(char *buffer) = 0;
};

} //namespace ilrd

#endif // ILRD_RD734_COMMAND_HPP