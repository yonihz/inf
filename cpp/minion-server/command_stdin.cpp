#include "command_stdin.hpp"
#include "logger.hpp"
#include "singleton.hpp"

#define UNUSED(x) (void)(x)

namespace ilrd
{

void StdInExitCmd::operator()(Reactor *reactor)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.Log(Logger::DEBUG, "Exit: Closing all sockets\n");
    reactor->Stop();
}

void StdInPlusCmd::operator()(Reactor *reactor)
{
    UNUSED(reactor);
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.IncOutputSeverity();
}

void StdInMinusCmd::operator()(Reactor *reactor)
{
    UNUSED(reactor);
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.DecOutputSeverity();
}

void StdInPingCmd::operator()(Reactor *reactor)
{
    UNUSED(reactor);
    Logger &logger = *(Singleton<Logger>::Instance());
    std::cout << "pong" << std::endl;
    logger.Log(Logger::DEBUG, "pong\n");
}

void StdInOutputCoutCmd::operator()(Reactor *reactor)
{
    UNUSED(reactor);
    Logger &logger = *(Singleton<Logger>::Instance());
    logger.Log(Logger::DEBUG, "SetOutput(std::cout)\n");
    logger.SetOutput(std::cout);
}

boost::shared_ptr<StdInCommand> CreatorStdInExitCmd()
{
    boost::shared_ptr<StdInCommand> command(new StdInExitCmd());
    return command;
}

boost::shared_ptr<StdInCommand> CreatorStdInPlusCmd()
{
    boost::shared_ptr<StdInCommand> command(new StdInPlusCmd());
    return command;
}

boost::shared_ptr<StdInCommand> CreatorStdInMinusCmd()
{
    boost::shared_ptr<StdInCommand> command(new StdInMinusCmd());
    return command;
}

boost::shared_ptr<StdInCommand> CreatorStdInPingCmd()
{
    boost::shared_ptr<StdInCommand> command(new StdInPingCmd());
    return command;
}

boost::shared_ptr<StdInCommand> CreatorStdInOutputCoutCmd()
{
    boost::shared_ptr<StdInCommand> command(new StdInOutputCoutCmd());
    return command;
}

} //namespace ilrd