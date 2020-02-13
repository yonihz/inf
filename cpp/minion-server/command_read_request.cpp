#include <fstream>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast; 

#include "command.hpp"
#include "logger.hpp"
#include "singleton.hpp"

namespace ilrd
{

class ReadRequestCmd : public Command
{
public:
    ReadRequestCmd();

    void operator()(char *buffer);
};

extern "C"
{
    boost::shared_ptr<Command> Creator();
    char GetKey();
}

ReadRequestCmd::ReadRequestCmd()
    : Command() {}

void ReadRequestCmd::operator()(char *buffer)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    std::string filename = "block" + lexical_cast<std::string>(*(size_t*)&(buffer[9]));
    std::ifstream block_file(filename.c_str());

    logger.Log(Logger::DEBUG, "Read request\n");

    buffer[9] = 1;
    block_file.read(&(buffer[10]), 4096); 
}

boost::shared_ptr<Command> Creator()
{
    boost::shared_ptr<Command> command(new ReadRequestCmd());
    return command;
}

char GetKey()
{
    return 0;
}

} //namespace ilrd