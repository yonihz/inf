#ifndef ILRD_RD734_SOCKET_HPP
#define ILRD_RD734_SOCKET_HPP

namespace ilrd
{

void InitAddrinfo(const char *ip, const char *port, int ai_family, int ai_socktype, int ai_flags, struct addrinfo **server_addrinfo);

/* frees serv_info, returns -1 or error */
int TCPServerBindSocket(struct addrinfo *serv_info);

/* frees serv_info, returns -1 or error */
int ClientConnectSocket(struct addrinfo *server_addrinfo);

/* frees serv_info, returns -1 or error */
int UDPServerBindSocket(struct addrinfo *server_addrinfo);

void PrintClientAddr(struct sockaddr_storage *client_addrinfo);

}

#endif // ILRD_RD734_SOCKET_HPP