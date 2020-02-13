// gd98 -c -fPIC command_write_request.cpp -I../logger/ -I../singleton/ -I../waitable_queue/ -I../thread/
// gd98 -c -fPIC command_read_request.cpp -I../logger/ -I../singleton/ -I../waitable_queue/ -I../thread/
// gd98 -shared command_read_request.o -o libcommand_read_request.so
// gd98 -shared command_write_request.o -o libcommand_write_request.so

// gd98 -c -fPIC ../logger/logger.cpp ../thread/thread.cpp -I../thread/ -I../logger/ -I../waitable_queue/ -I../singleton/
// gd98 -shared logger.o thread.o -o liblogger.so

// gd98 -fPIC server_test.cpp server.cpp command_stdin.cpp ../project/reactor/reactor.cpp ../project/reactor/fd_listener.cpp  ../socket/socket.cpp -I../factory/ -I../socket/ -I../project/reactor/ -I../logger/ -I../singleton/ -I../waitable_queue/ -I../thread/ -pthread -lboost_system -Wl,-rpath,. -L. -llogger -ldl -rdynamic -o server.out

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

    UDPProcessRequest udp_process_request(udp_listener.GetSocket(), &reactor);

    // reactor.AddFD(tcp_listener.GetSocket(), Reactor::READ, tcp_listener);
    reactor.AddFD(udp_listener.GetSocket(), Reactor::READ, udp_process_request);
    reactor.AddFD(STDIN_FILENO, Reactor::READ, stdin_listener);

    reactor.Run();

    udp_listener.CloseSocket();
    // tcp_listener.CloseSocket();
    // tcp_listener.CloseAllConnections();

    return 0;
}