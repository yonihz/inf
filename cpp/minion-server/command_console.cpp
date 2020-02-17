#include "command_console.hpp"
#include "logger.hpp"
#include "singleton.hpp"

#define UNUSED(x) (void)(x)

namespace ilrd
{

void ConsoleExitCmd::operator()(Reactor *reactor)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.Log(Logger::DEBUG, "Exit: Closing all sockets\n");
    reactor->Stop();
}

void ConsolePlusCmd::operator()(Reactor *reactor)
{
    UNUSED(reactor);
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.IncOutputSeverity();
}

void ConsoleMinusCmd::operator()(Reactor *reactor)
{
    UNUSED(reactor);
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.DecOutputSeverity();
}

void ConsolePingCmd::operator()(Reactor *reactor)
{
    UNUSED(reactor);
    Logger &logger = *(Singleton<Logger>::Instance());
    std::cout << "pong" << std::endl;
    logger.Log(Logger::DEBUG, "pong\n");
}

void ConsoleOutputCoutCmd::operator()(Reactor *reactor)
{
    UNUSED(reactor);
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.Log(Logger::DEBUG, "SetOutput(std::cout)\n");
    logger.SetOutput(std::cout);
}

boost::shared_ptr<ConsoleCommand> CreatorConsoleExitCmd()
{
    boost::shared_ptr<ConsoleCommand> command(new ConsoleExitCmd());
    return command;
}

boost::shared_ptr<ConsoleCommand> CreatorConsolePlusCmd()
{
    boost::shared_ptr<ConsoleCommand> command(new ConsolePlusCmd());
    return command;
}

boost::shared_ptr<ConsoleCommand> CreatorConsoleMinusCmd()
{
    boost::shared_ptr<ConsoleCommand> command(new ConsoleMinusCmd());
    return command;
}

boost::shared_ptr<ConsoleCommand> CreatorConsolePingCmd()
{
    boost::shared_ptr<ConsoleCommand> command(new ConsolePingCmd());
    return command;
}

boost::shared_ptr<ConsoleCommand> CreatorConsoleOutputCoutCmd()
{
    boost::shared_ptr<ConsoleCommand> command(new ConsoleOutputCoutCmd());
    return command;
}

} //namespace ilrd