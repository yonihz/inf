#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

#include "socket.hpp"

namespace ilrd
{

void CreateServer(int tcp_port, int udp_port);

void *ConsoleThread(void* arg);

void *TCPServerThread(void *server_in);

void *TCPConnectionThread(void *new_sockfd_voidptr);

void *UDPServerThread(void *server_in);

void UDPServerLoop(int sockfd);

void *UDPBroadcastServerThread(void *server_in);

void UDPBroadcastServerLoop(int sockfd);

}

#endif // ILRD_RD734_SERVER_HPP