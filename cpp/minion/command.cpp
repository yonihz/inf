#include <string>
#include <fstream>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast; 

#include "command.hpp"

namespace ilrd
{

CmdArgs::CmdArgs(int sockfd_, char *buffer_)
        : m_sockfd(sockfd_), 
        m_buffer(buffer_), 
        m_client_addrinfo(), 
        m_client_addrlen(sizeof(m_client_addrinfo)) {}

Command::Command(CmdArgs &args_)
    : m_args(args_) {}

ReadRequestCmd::ReadRequestCmd(CmdArgs &args_)
    : Command(args_) {}

void ReadRequestCmd::operator()(void)
{
    std::string filename = "block" + lexical_cast<std::string>(*(size_t*)&(m_args.m_buffer[9]));
    std::ifstream block_file(filename.c_str());

    m_args.m_buffer[9] = 1;
    block_file.read(&(m_args.m_buffer[10]), 4096);


    sendto(m_args.m_sockfd, m_args.m_buffer, 4106, MSG_DONTWAIT, (const struct sockaddr *)&m_args.m_client_addrinfo, m_args.m_client_addrlen);    
}

WriteRequestCmd::WriteRequestCmd(CmdArgs &args_)
    : Command(args_) {}

void WriteRequestCmd::operator()(void)
{
    std::string filename = "block" + lexical_cast<std::string>(*(size_t*)&(m_args.m_buffer[9]));
    std::ofstream block_file(filename.c_str());

    block_file.write(&(m_args.m_buffer[17]), 4096);

    m_args.m_buffer[9] = 1;

    sendto(m_args.m_sockfd, m_args.m_buffer, 10, MSG_DONTWAIT, (const struct sockaddr *)&m_args.m_client_addrinfo, m_args.m_client_addrlen);  
}

boost::shared_ptr<Command> CreateReadRequestCmd(CmdArgs &args)
{
    boost::shared_ptr<Command> command(new ReadRequestCmd(args));
    return command;
}

boost::shared_ptr<Command> CreateWriteRequestCmd(CmdArgs &args)
{
    boost::shared_ptr<Command> command(new WriteRequestCmd(args));
    return command;
}

}

