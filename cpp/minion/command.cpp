#include <string>
#include <fstream>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast; 

#include "command.hpp"

namespace ilrd
{

CmdArgs::CmdArgs(int sockfd_, char *buffer_)
    : m_sockfd(sockfd_), m_buffer(buffer_), m_client_addrinfo(), m_client_addrlen(sizeof(m_client_addrinfo)) {}

void ReadRequestCmd::operator()(CmdArgs &args)
{
    std::string filename = "block" + lexical_cast<std::string>(*(size_t*)&(args.m_buffer[9]));
    std::ifstream block_file(filename.c_str());

    args.m_buffer[9] = 1;
    block_file.read(&(args.m_buffer[10]), 4096);


    sendto(args.m_sockfd, args.m_buffer, 4106, MSG_DONTWAIT, (const struct sockaddr *)&args.m_client_addrinfo, args.m_client_addrlen);    
}

void WriteRequestCmd::operator()(CmdArgs &args)
{
    std::string filename = "block" + lexical_cast<std::string>(*(size_t*)&(args.m_buffer[9]));
    std::ofstream block_file(filename.c_str());

    block_file.write(&(args.m_buffer[17]), 4096);

    args.m_buffer[9] = 1;

    sendto(args.m_sockfd, args.m_buffer, 10, MSG_DONTWAIT, (const struct sockaddr *)&args.m_client_addrinfo, args.m_client_addrlen);  
}

}

