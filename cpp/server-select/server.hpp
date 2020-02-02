#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

#include "socket.hpp"

namespace ilrd
{

void CreateServer(int tcp_port, int udp_port);

void ServerConsole(void);

int UDPServerGetSocket(int port);

ssize_t UDPServerRead(int socket_fd);

int TCPServerGetSocket(int port);

ssize_t TCPServerRead(int sock_fd);

}

#endif // ILRD_RD734_SERVER_HPP