#ifndef ILRD_RD734_COMMAND_STDIN_HPP
#define ILRD_RD734_COMMAND_STDIN_HPP

#include <netdb.h>

#include <boost/shared_ptr.hpp>

#include "reactor.hpp"

namespace ilrd
{

class StdInCommand
{
public:
    virtual ~StdInCommand() {}

    virtual void operator()(Reactor *reactor) = 0;
};

class StdInExitCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

class StdInPlusCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

class StdInMinusCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

class StdInPingCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

class StdInOutputCoutCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

boost::shared_ptr<StdInCommand> CreatorStdInExitCmd();
boost::shared_ptr<StdInCommand> CreatorStdInPlusCmd();
boost::shared_ptr<StdInCommand> CreatorStdInMinusCmd();
boost::shared_ptr<StdInCommand> CreatorStdInPingCmd();
boost::shared_ptr<StdInCommand> CreatorStdInOutputCoutCmd();

} //namespace ilrd

#endif // ILRD_RD734_COMMAND_STDIN_HPP