#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

#include <set>

#include "socket.hpp"
#include "reactor.hpp"

namespace ilrd
{

class ConsoleListener
{
public:
    ConsoleListener(int sockfd_, Reactor *reactor_);
    ~ConsoleListener();

    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class UDPProcessRequest
{
public:
    UDPProcessRequest(int sockfd_, Reactor *reactor_);
    ~UDPProcessRequest();

    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class TCPProcessRequest
{
public:
    TCPProcessRequest(int sockfd_, Reactor *reactor_, TCPListener *tcp_listener_);
    ~TCPProcessRequest();

    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
    TCPListener *m_tcp_listener;
};

class TCPListener
{
public:
    TCPListener(int port_, Reactor *reactor_);
    ~TCPListener();

    int CreateSocket();
    int GetSocket();
    int Listen();
    void CloseSocket();
    void CloseAllConnections();
    void CloseConnection(int sockfd);

    void operator()(void);

private:
    const int backlog = 10;
    int m_port;
    int m_sockfd;
    boost::shared_ptr< std::set<int> > m_connections;
    Reactor *m_reactor;
};

class UDPListener
{
public:
    UDPListener(int port_, Reactor *reactor_);
    ~UDPListener();

    int CreateSocket();
    int GetSocket();
    void CloseSocket();

    void operator()(void);

private:
    int m_port;
    int m_sockfd;
    Reactor *m_reactor;
};

}

#endif // ILRD_RD734_SERVER_HPP