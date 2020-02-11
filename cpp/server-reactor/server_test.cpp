// gd98 server_test.cpp server.cpp ../thread/thread.cpp ../project/reactor/reactor.cpp ../project/reactor/fd_listener.cpp  ../socket/socket.cpp ../logger/logger.cpp -I../factory/ -I../logger/ -I../socket/ -I../waitable_queue/ -I../singleton/ -I../project/reactor/ -I../thread/ -pthread -lboost_system -o server.out

#include <cstdlib>
#include <iostream>

#include "server.hpp"
#include "logger.hpp"
#include "singleton.hpp"

using namespace ilrd;

int main(int argc, char *argv[])
{  
    if (argc != 3)
    {
        std::cout << "Error: need 2 ports as arguments to run" << std::endl;
        return 0;
    }

    Reactor reactor;

    Logger &logger = *(Singleton<Logger>::Instance());
    int status;

    ConsoleListener console_listener(STDIN_FILENO, &reactor);

    UDPListener udp_listener(atoi(argv[2]), &reactor);
    status = udp_listener.CreateSocket();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "UDP server: failed to bind\n");
        return 0;
    }

    TCPListener tcp_listener(atoi(argv[1]), &reactor);
    status = tcp_listener.CreateSocket();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "TCP server: failed to bind\n");
        return 0;
    } 

    status = tcp_listener.Listen();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "TCP server listen error\n");
    }

    logger.Log(Logger::INFO, "TCP server: waiting for connections...\n");

    
    reactor.AddFD(tcp_listener.GetSocket(), Reactor::READ, tcp_listener);
    reactor.AddFD(udp_listener.GetSocket(), Reactor::READ, udp_listener);
    reactor.AddFD(STDIN_FILENO, Reactor::READ, console_listener);

    reactor.Run();

    return 0;
}