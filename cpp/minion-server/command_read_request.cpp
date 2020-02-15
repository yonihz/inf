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
    std::string filename =
        "block" +
        lexical_cast<std::string>(*(size_t*)&(buffer[SEND_BLOCK_IDX_BYTE]));
    std::ifstream block_file(filename.c_str());

    logger.Log(Logger::DEBUG, "Read request\n");

    buffer[REPLY_STATUS_BYTE] = SUCCESS;
    block_file.read(&(buffer[REPLY_DATA_BYTE]), BLOCK_SIZE); 
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