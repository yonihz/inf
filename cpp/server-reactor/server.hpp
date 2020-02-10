#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

#include <iostream> // delete

#include "socket.hpp"
#include "reactor.hpp"

namespace ilrd
{

class ServerConsoleFunction
{
public:
    ServerConsoleFunction(int sockfd_, Reactor *reactor_);
    ~ServerConsoleFunction() { std::cout << "ServerConsoleFunction Dtor" << std::endl; }
    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class TCPListenerFunction
{
public:
    TCPListenerFunction(int sockfd_, Reactor *reactor_);
    ~TCPListenerFunction() { std::cout << "TCPListenerFunction Dtor" << std::endl; }
    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class UDPServerReadFunction
{
public:
    UDPServerReadFunction(int sockfd_, Reactor *reactor_);
    ~UDPServerReadFunction() { std::cout << "TCPListenerFunction Dtor" << std::endl; }
    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class TCPServerReadFunction
{
public:
    TCPServerReadFunction(int sockfd_, Reactor *reactor_);
    ~TCPServerReadFunction();
    // ~TCPServerReadFunction() {}
    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class TCPServer
{
public:
    TCPServer(int port_);
    ~TCPServer();
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
    ~UDPServer();
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