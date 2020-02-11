#include <fstream>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast;

#include "command.hpp"

namespace ilrd
{

class WriteRequestCmd : public Command
{
public:
    WriteRequestCmd();

    void operator()(int sockfd, char *buffer, struct addrinfo *client_addrinfo, socklen_t *client_addrlen);
};

extern "C"
{
    boost::shared_ptr<Command> Creator();
    char GetKey();
}

WriteRequestCmd::WriteRequestCmd()
: Command() {}

void WriteRequestCmd::operator()(int sockfd, char *buffer, struct addrinfo *client_addrinfo, socklen_t *client_addrlen)
{
    std::string filename = "block" + lexical_cast<std::string>(*(size_t*)&(buffer[9]));
    std::ofstream block_file(filename.c_str());

    // logger.Log(Logger::DEBUG, "cmd write log: DEBUG\n");
    // logger.Log(Logger::INFO, "cmd write log: INFO\n");
    // logger.Log(Logger::WARNING, "cmd write log: WARNING\n");
    // logger.Log(Logger::ERROR, "cmd write log: ERROR\n");

    block_file.write(&(buffer[17]), 4096);

    buffer[9] = 1;

    sendto(sockfd, buffer, 10, MSG_DONTWAIT, (const struct sockaddr *)client_addrinfo, *client_addrlen);  
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