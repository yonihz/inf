#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

#include <set>

#include <boost/shared_ptr.hpp>

#include "socket.hpp"
#include "reactor.hpp"
#include "factory.hpp"

namespace ilrd
{

class StdInCommand
{
public:
    virtual ~StdInCommand() {}

    virtual void operator()(Reactor *reactor) = 0;
};

class StdInExitCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

class StdInPlusCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

class StdInMinusCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

class StdInPingCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

class StdInOutputCoutCmd : public StdInCommand
{
public:
    void operator()(Reactor *reactor);
};

boost::shared_ptr<StdInCommand> CreatorStdInExitCmd();
boost::shared_ptr<StdInCommand> CreatorStdInPlusCmd();
boost::shared_ptr<StdInCommand> CreatorStdInMinusCmd();
boost::shared_ptr<StdInCommand> CreatorStdInPingCmd();
boost::shared_ptr<StdInCommand> CreatorStdInOutputCoutCmd();

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
    int m_sockfd;
    Reactor *m_reactor;
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