#include <cstdlib>
#include <iostream>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast; 

#include "server.hpp"
#include "dir_monitor.hpp"
#include "plugin_loader.hpp"
#include "logger_configurator.hpp"
#include "event_handler.hpp"
#include "logger.hpp"
#include "singleton.hpp"

using namespace ilrd;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " + lexical_cast<std::string>(argv[0]) + " PORT\n";
        return 0;
    }

    Reactor reactor;

    ServerConsole server_console(STDIN_FILENO, &reactor);

    CommandManager cmd_manager(&reactor);
    UDPServer udp_server(NULL, atoi(argv[1]), cmd_manager, &reactor);
    udp_server.Init();

    std::string addons_dir("./add_ons/");
    DirMonitor dir_monitor(addons_dir, &cmd_manager, &reactor);
    dir_monitor.Init();

    udp_server.AddToReactor();
    server_console.AddToReactor();
    dir_monitor.AddToReactor();
    // std::cout << "after reactor\n";

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