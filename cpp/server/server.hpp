#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

#include "socket.hpp"
#include "logger.hpp"

void CreateServer(const char *tcp_port, const char *udp_port, const char *bc_port);

void *ConsoleThread(void* arg);

void *TCPServerThread(void *server_in);

void TCPServerLoop(int new_socket_fd);

void *UDPServerThread(void *server_in);

void UDPServerLoop(int socket_fd);

void *UDPBroadcastServerThread(void *server_in);

void UDPBroadcastServerLoop(int socket_fd);

#endif // ILRD_RD734_SERVER_HPP