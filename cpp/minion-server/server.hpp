#ifndef ILRD_RD734_SERVER_HPP
#define ILRD_RD734_SERVER_HPP

#include <set>

#include <boost/shared_ptr.hpp>

#include "socket.hpp"
#include "reactor.hpp"
#include "factory.hpp"
#include "command.hpp"
#include "command_console.hpp"

namespace ilrd
{

class ConsoleCmdManager
{
public:
    ConsoleCmdManager(Reactor *reactor_);
    void RunCommand(std::string str_);
    void AddCommand(std::string str_, boost::shared_ptr<ConsoleCommand>(*creator_)(void));

private:
    Factory<
        boost::shared_ptr<ConsoleCommand>, 
        std::string,
        void, 
        boost::shared_ptr<ConsoleCommand>(*)(void)> 
        m_factory;
    Reactor *m_reactor;
};

class ConsoleFD
{
public:
    ConsoleFD(int fd_);
    int GetFD();

private:
    int m_fd;
};

class ServerConsole
{
public:
    ServerConsole(int fd_, Reactor *reactor_);
    void AddToReactor();

    void operator()(void);

private:
    const static int MAXDATASIZE = 100;
    ConsoleCmdManager m_cmd_manager;
    ConsoleFD m_console_fd;
    Reactor *m_reactor;
};

class UDPServerSocket
{
public:
    UDPServerSocket(const char *ip_, int port_);

    int Init();
    int GetFD();
    void CloseSocket();

private:
    const char *m_ip;
    int m_port;
    int m_sockfd;
};

class UDPCmdManager
{
public:
    UDPCmdManager(Reactor *reactor_);

    void RunCommand(char c_, char *buffer_);
    void AddCommand(char c_, boost::shared_ptr<Command>(*creator_)(void));

    void operator()(void);
private:
    Reactor *m_reactor;
    Factory<boost::shared_ptr<Command>, char, void, boost::shared_ptr<Command>(*)(void)> m_factory;
};

class UDPServer
{
public:
    UDPServer(const char *ip_, int port_, Reactor *reactor_);
    ~UDPServer();
    
    int Init();
    void AddToReactor();

    void operator()(void);
private:
    const static int MAXDATASIZE = 100;
    const static size_t WRITE_REPLY_LEN = 10;
    const static size_t READ_REPLY_LEN = 4106;
    const static size_t BUFFER_SIZE = 4114;
    const static size_t REQUEST_TYPE_BYTE = 0;
    size_t m_reply_len[2];
    UDPCmdManager m_cmd_manager;
    UDPServerSocket m_socket;
    Reactor *m_reactor;
};

} //namespace ilrd

#endif // ILRD_RD734_SERVER_HPP

// class TCPServer
// {
// public:
//     TCPServer(const char *ip, int port_, Reactor *reactor_);

//     int Init();
//     void AddToReactor();

//     void operator()(void);
// private:
//     const static int MAXDATASIZE = 100;
//     TCPCmdManager m_cmd_manager;
//     TCPServerSocket m_socket;
//     Reactor *m_reactor;
// };

// class TCPServerSocket
// {
// public:
//     TCPServerSocket(const char *ip_, int port_);

//     int Init();
//     int GetSocket();
//     void CloseSocket();
//     void CloseAllConnections();
//     void CloseConnection(int sockfd);

// private:
//     int Listen();
//     int CreateSocket();
//     const static int BACKLOG = 10;
//     const char *m_ip
//     int m_port;
//     int m_sockfd;
//     boost::shared_ptr< std::set<int> > m_connections;
// };

// class TCPCmdManager
// {
// public:
//     TCPCmdManager(Reactor *reactor_);

//     void operator()(void);

// private:
//     int m_sockfd;
//     Reactor *m_reactor;
//     TCPServerSocket *m_tcp_server_socket;
// };