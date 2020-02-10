#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

#include "socket.hpp"
#include "reactor.hpp"
#include "factory.hpp"

namespace ilrd
{

void CloseAllFD(Reactor *reactor);

class ServerConsoleFunction
{
public:
    ServerConsoleFunction(int sockfd_, Reactor *reactor_);
    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class TCPListenerFunction
{
public:
    TCPListenerFunction(int sockfd_, Reactor *reactor_);
    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class UDPServerReadFunction
{
public:
    UDPServerReadFunction(int sockfd_, Reactor *reactor_);
    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
    Factory<boost::shared_ptr<Command>, char, void, boost::shared_ptr<Command>(*)(void)> m_factory;
};

class TCPServerReadFunction
{
public:
    TCPServerReadFunction(int sockfd_, Reactor *reactor_);
    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class TCPServer
{
public:
    TCPServer(int port_);
    int CreateSocket();
    int GetSocket();
    int Listen();

private:
    int m_port;
    int m_sockfd;
    int m_backlog;
};

class UDPServer
{
public:
    UDPServer(int port_);
    int CreateSocket();
    int GetSocket();

private:
    int m_port;
    int m_sockfd;
};

class Server
{
public:
    Server(int tcp_port, int udp_port);
    void Start();

private:
    TCPServer m_tcp_server;
    UDPServer m_udp_server;
    Reactor m_reactor;
};

}

#endif // ILRD_RD734_SERVER_HPP