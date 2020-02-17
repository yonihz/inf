#ifndef ILRD_RD734_COMMAND_STDIN_HPP
#define ILRD_RD734_COMMAND_STDIN_HPP

#include <netdb.h>

#include <boost/shared_ptr.hpp>

#include "reactor.hpp"

namespace ilrd
{

class ConsoleCommand
{
public:
    virtual ~ConsoleCommand() {}

    virtual void operator()(Reactor *reactor) = 0;
};

class ConsoleExitCmd : public ConsoleCommand
{
public:
    void operator()(Reactor *reactor);
};

class ConsolePlusCmd : public ConsoleCommand
{
public:
    void operator()(Reactor *reactor);
};

class ConsoleMinusCmd : public ConsoleCommand
{
public:
    void operator()(Reactor *reactor);
};

class ConsolePingCmd : public ConsoleCommand
{
public:
    void operator()(Reactor *reactor);
};

class ConsoleOutputCoutCmd : public ConsoleCommand
{
public:
    void operator()(Reactor *reactor);
};

boost::shared_ptr<ConsoleCommand> CreatorConsoleExitCmd();
boost::shared_ptr<ConsoleCommand> CreatorConsolePlusCmd();
boost::shared_ptr<ConsoleCommand> CreatorConsoleMinusCmd();
boost::shared_ptr<ConsoleCommand> CreatorConsolePingCmd();
boost::shared_ptr<ConsoleCommand> CreatorConsoleOutputCoutCmd();

} //namespace ilrd

#endif // ILRD_RD734_COMMAND_STDIN_HPP