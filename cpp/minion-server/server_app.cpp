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
        std::cout << "Error: need 1 ports as arguments to run" << std::endl;
        return 0;
    }

    Reactor reactor;

    Logger &logger = *(Singleton<Logger>::Instance());
    int status;

    ServerConsole server_console(STDIN_FILENO, &reactor);

    UDPServer udp_server(NULL, atoi(argv[1]), &reactor);
    status = udp_server.Init();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "UDP server: failed to init\n");
        return 0;
    }

    udp_server.AddToReactor();
    server_console.AddToReactor();

    reactor.Run();

    return 0;
}


    // TCPListener tcp_listener(atoi(argv[1]), &reactor);
    // status = tcp_listener.Init();

    // if (status == -1)
    // {
    //     logger.Log(Logger::ERROR, "TCP listener: failed to init\n");
    //     return 0;
    // }

    // reactor.AddFD(tcp_listener.GetSocket(), Reactor::READ, tcp_listener);

    // tcp_listener.CloseSocket();
    // tcp_listener.CloseAllConnections();