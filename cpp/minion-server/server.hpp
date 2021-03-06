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

class ConsoleCommandManager
{
public:
    ConsoleCommandManager(Reactor *reactor_);
    void RunCommand(std::string str_);
    void AddCommand(std::string str_, boost::shared_ptr<ConsoleCommand>(*creator_)(void));

    void operator()(const char *name_);
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
    ConsoleCommandManager m_cmd_manager;
    ConsoleFD m_console_fd;
    Reactor *m_reactor;
};

class UDPServerSocket
{
public:
    UDPServerSocket(const char *ip_, int port_);
    ~UDPServerSocket();

    int Init();
    int GetFD();
    void CloseSocket();

private:
    const char *m_ip;
    int m_port;
    int m_sockfd;
};

class UDPServer
{
public:
    UDPServer(const char *ip_, int port_, CommandManager &cmd_manager_, Reactor *reactor_);
    
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
    CommandManager &m_cmd_manager;
    boost::shared_ptr<UDPServerSocket> m_socket;
    Reactor *m_reactor;
};

class TCPServerSocket
{
public:
    TCPServerSocket(const char *ip_, int port_);
    ~TCPServerSocket();

    int Init();
    int GetFD();
    void CloseSocket();


private:
    int CreateSocket();
    int Listen();
    const static int BACKLOG = 10;
    const char *m_ip;
    int m_port;
    int m_sockfd;
};

class TCPServer
{
public:
    TCPServer(const char *ip_, int port_, CommandManager &cmd_manager_, Reactor *reactor_);
    
    int Init();
    void AddToReactor();

    void operator()(void);
    
private:
    const static int MAXDATASIZE = 100;
    CommandManager &m_cmd_manager;
    boost::shared_ptr<TCPServerSocket> m_socket;
    Reactor *m_reactor;
};

class TCPConnectionSocket
{
public:
    TCPConnectionSocket(int sockfd_);
    ~TCPConnectionSocket();

    int GetFD();
    void CloseSocket();

private:
    int m_sockfd;
};

class TCPConnection
{
public:
    TCPConnection(int sockfd_, CommandManager cmd_manager_, Reactor *reactor_);

    void AddToReactor();

    void operator()(void);
    
private:
    const static int MAXDATASIZE = 100;
    boost::shared_ptr<TCPConnectionSocket> m_socket;
    CommandManager &m_cmd_manager;
    Reactor *m_reactor;
};

} //namespace ilrd

#endif // ILRD_RD734_SERVER_HPP