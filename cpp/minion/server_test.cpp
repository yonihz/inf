// gd98 server_test.cpp server.cpp command.cpp ../thread/thread.cpp ../project/reactor/reactor.cpp ../project/reactor/fd_listener.cpp  ../socket/socket.cpp ../logger/logger.cpp -I../factory/ -I../logger/ -I../socket/ -I../waitable_queue/ -I../singleton/ -I../project/reactor/ -I../thread/ -pthread -lboost_system -o server.out

// with .so: 
// gd98 -c -fPIC command.cpp -o command.o
// gd98 -shared command.o -o libcommand.so
// gd98 server_test.cpp server.cpp ../thread/thread.cpp ../project/reactor/reactor.cpp ../project/reactor/fd_listener.cpp  ../socket/socket.cpp ../logger/logger.cpp -I../factory/ -I../logger/ -I../socket/ -I../waitable_queue/ -I../singleton/ -I../project/reactor/ -I../thread/ -pthread -lboost_system -Wl,-rpath,. -lcommand -L. -o server.out

// with .so: 
// gd98 -c -fPIC command_write_request.cpp -o command_write_request.o
// gd98 -c -fPIC command_read_request.cpp -o command_read_request.o
// gd98 -shared command_read_request.o -o libcommand_read_request.so
// gd98 -shared command_write_request.o -o libcommand_write_request.so
// gd98 server_test.cpp server.cpp ../thread/thread.cpp ../project/reactor/reactor.cpp ../project/reactor/fd_listener.cpp  ../socket/socket.cpp ../logger/logger.cpp -I../factory/ -I../logger/ -I../socket/ -I../waitable_queue/ -I../singleton/ -I../project/reactor/ -I../thread/ -pthread -lboost_system -Wl,-rpath,. -lcommand -L. -ldl -o server.out

#include <cstdlib>
#include <iostream>

#include "server.hpp"
#include "logger.hpp"
#include "singleton.hpp"

using namespace ilrd;

int main(int argc, char *argv[])
{  
    if (argc != 2)
    {
        std::cout << "Error: need 1 port as argument to run" << std::endl;
        return 0;
    }

    Logger &logger = *(Singleton<Logger>::Instance());
    int status;

    UDPServer udp_server(atoi(argv[1]));
    status = udp_server.CreateSocket();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "UDP server: failed to bind\n");
        return 0;
    }

    // TCPServer tcp_server(atoi(argv[1]));
    // status = tcp_server.CreateSocket();

    // if (status == -1)
    // {
    //     logger.Log(Logger::ERROR, "TCP server: failed to bind\n");
    //     return 0;
    // } 

    // status = tcp_server.Listen();

    // if (status == -1)
    // {
    //     logger.Log(Logger::ERROR, "TCP server listen error\n");
    // }

    // logger.Log(Logger::INFO, "TCP server: waiting for connections...\n");

    Reactor reactor;
    // m_reactor.AddFD(
    //     tcp_server.GetSocket(),
    //     Reactor::READ,
    //     TCPListenerFunction(tcp_server.GetSocket(), &reactor));
    
    reactor.AddFD(
        udp_server.GetSocket(),
        Reactor::READ,
        UDPServerReadFunction(udp_server.GetSocket(), &reactor));
    
    reactor.AddFD(
        STDIN_FILENO,
        Reactor::READ,
        ServerConsoleFunction(STDIN_FILENO, &reactor));

    reactor.Run();

    return 0;
}