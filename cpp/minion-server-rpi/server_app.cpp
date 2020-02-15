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

    StdInListener stdin_listener(STDIN_FILENO, &reactor);

    UDPListener udp_listener(atoi(argv[1]), &reactor);
    status = udp_listener.Init();

    if (status == -1)
    {
        logger.Log(Logger::ERROR, "UDP listener: failed to init\n");
        return 0;
    }

    // TCPListener tcp_listener(atoi(argv[1]), &reactor);
    // status = tcp_listener.Init();

    // if (status == -1)
    // {
    //     logger.Log(Logger::ERROR, "TCP listener: failed to init\n");
    //     return 0;
    // } 

    UDPRequestMgr udp_request_mgr(udp_listener.GetSocket(), &reactor);

    // reactor.AddFD(tcp_listener.GetSocket(), Reactor::READ, tcp_listener);
    reactor.AddFD(udp_listener.GetSocket(), Reactor::READ, udp_request_mgr);
    reactor.AddFD(STDIN_FILENO, Reactor::READ, stdin_listener);

    reactor.Run();

    udp_listener.CloseSocket();
    // tcp_listener.CloseSocket();
    // tcp_listener.CloseAllConnections();

    return 0;
}