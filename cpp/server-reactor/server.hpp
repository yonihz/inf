#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

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
    TCPProcessRequest(int sockfd_, Reactor *reactor_);
    ~TCPProcessRequest();

    void operator()(void);

private:
    int m_sockfd;
    Reactor *m_reactor;
};

class TCPListener
{
public:
    TCPListener(int port_, Reactor *reactor_);
    ~TCPListener();

    int CreateSocket();
    int GetSocket();
    int Listen();

    void operator()(void);

private:
    int m_port;
    int m_sockfd;
    int m_backlog;
    Reactor *m_reactor;
    boost::shared_ptr< std::vector<int> > m_connected_fds;
};

class UDPListener
{
public:
    UDPListener(int port_, Reactor *reactor_);
    ~UDPListener();

    int CreateSocket();
    int GetSocket();

    void operator()(void);

private:
    int m_port;
    int m_sockfd;
    Reactor *m_reactor;
};

}

#endif // ILRD_RD734_SERVER_HPP