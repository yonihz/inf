#include <signal.h>
#include <pthread.h>

#include "socket.h"

void CreateServer(int tcp_port, int udp_port, int bc_port);

void *TCPServerThread(void *server_in);

void TCPServerLoop(int new_socket_fd);

void *UDPServerThread(void *server_in);

void UDPServerLoop(int socket_fd);

void *UDPBroadcastServerThread(void *server_in);

void UDPBroadcastServerLoop(int socket_fd);