#include <fstream>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast;

#include "command.hpp"
#include "logger.hpp"
#include "singleton.hpp"

namespace ilrd
{

class WriteRequestCmd : public Command
{
public:
    WriteRequestCmd();

    void operator()(char *buffer);
};

extern "C"
{
    boost::shared_ptr<Command> Creator();
    char GetKey();
}

WriteRequestCmd::WriteRequestCmd()
: Command() {}

void WriteRequestCmd::operator()(char *buffer)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    std::string filename = 
        "block" + 
        lexical_cast<std::string>(*(size_t*)&(buffer[SEND_BLOCK_IDX_BYTE]));

    std::ofstream block_file(filename.c_str());

    logger.Log(Logger::DEBUG, "Write request\n");

    block_file.write(&(buffer[SEND_DATA_BYTE]), BLOCK_SIZE);

    buffer[REPLY_STATUS_BYTE] = SUCCESS; 
}

boost::shared_ptr<Command> Creator()
{
    boost::shared_ptr<Command> command(new WriteRequestCmd());
    return command;
}

char GetKey()
{
    return 1;
}

} //namespace ilrd