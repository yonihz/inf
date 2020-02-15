#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

#include <set>

#include <boost/shared_ptr.hpp>

#include "socket.hpp"
#include "reactor.hpp"
#include "factory.hpp"
#include "command.hpp"
#include "command_stdin.hpp"

namespace ilrd
{

class StdInListener
{
public:
    StdInListener(int sockfd_, Reactor *reactor_);

    void operator()(void);

private:
    const static int MAXDATASIZE = 100;
    int m_sockfd;
    Reactor *m_reactor;
    Factory<boost::shared_ptr<StdInCommand>, std::string, void, boost::shared_ptr<StdInCommand>(*)(void)> m_factory;
};

class TCPListener
{
public:
    TCPListener(int port_, Reactor *reactor_);

    int Init();
    int GetSocket();
    void CloseSocket();
    void CloseAllConnections();
    void CloseConnection(int sockfd);

    void operator()(void);

private:
    int Listen();
    int CreateSocket();
    const static int BACKLOG = 10;
    int m_port;
    int m_sockfd;
    boost::shared_ptr< std::set<int> > m_connections;
    Reactor *m_reactor;
};

class UDPListener
{
public:
    UDPListener(int port_, Reactor *reactor_);

    int Init();
    int GetSocket();
    void CloseSocket();

private:
    int CreateSocket();
    int m_port;
    int m_sockfd;
    Reactor *m_reactor;
};

class UDPProcessRequest
{
public:
    UDPProcessRequest(int sockfd_, Reactor *reactor_);

    void operator()(void);

private:
    const static int MAXDATASIZE = 100;
    const static size_t WRITE_REPLY_LEN = 10;
    const static size_t READ_REPLY_LEN = 4106;
    const static size_t BUFFER_SIZE = 4114;
    const static size_t REQUEST_TYPE_BYTE = 0;
    int m_sockfd;
    Reactor *m_reactor;
    Factory<boost::shared_ptr<Command>, char, void, boost::shared_ptr<Command>(*)(void)> m_factory;
    size_t m_reply_len[2];
};

class TCPProcessRequest
{
public:
    TCPProcessRequest(int sockfd_, Reactor *reactor_, TCPListener *tcp_listener_);

    void operator()(void);

private:
    const static int MAXDATASIZE = 100;
    int m_sockfd;
    Reactor *m_reactor;
    TCPListener *m_tcp_listener;
};

}

#endif // ILRD_RD734_SERVER_HPP