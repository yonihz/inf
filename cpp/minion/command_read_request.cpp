#include <fstream>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast; 

#include "command.hpp"

namespace ilrd
{

class ReadRequestCmd : public Command
{
public:
    ReadRequestCmd();

    void operator()(int sockfd, char *buffer, struct addrinfo *client_addrinfo, socklen_t *client_addrlen);
};

extern "C"
{
    boost::shared_ptr<Command> Creator();
    char GetKey();
}

ReadRequestCmd::ReadRequestCmd()
    : Command() {}

void ReadRequestCmd::operator()(int sockfd, char *buffer, struct addrinfo *client_addrinfo, socklen_t *client_addrlen)
{
    std::string filename = "block" + lexical_cast<std::string>(*(size_t*)&(buffer[9]));
    std::ifstream block_file(filename.c_str());

    // logger.Log(Logger::DEBUG, "cmd write log: DEBUG\n");
    // logger.Log(Logger::INFO, "cmd write log: INFO\n");
    // logger.Log(Logger::WARNING, "cmd write log: WARNING\n");
    // logger.Log(Logger::ERROR, "cmd write log: ERROR\n");

    buffer[9] = 1;
    block_file.read(&(buffer[10]), 4096);

    sendto(sockfd, buffer, 4106, MSG_DONTWAIT, (const struct sockaddr *)client_addrinfo, *client_addrlen);    
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