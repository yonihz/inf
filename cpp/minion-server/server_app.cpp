#include <cstdlib>
#include <iostream>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast; 

#include "server.hpp"
#include "dir_monitor.hpp"
#include "plugin_loader.hpp"
#include "logger_configurator.hpp"
#include "logger.hpp"
#include "singleton.hpp"
#include "dispatcher.hpp"

using namespace ilrd;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " + lexical_cast<std::string>(argv[0]) + " PORT\n";
        return 0;
    }

    // if (argc != 3)
    // {
    //     std::cout << "Usage: " + lexical_cast<std::string>(argv[0]) + " UDP_PORT TCP_PORT\n";
    //     return 0;
    // }

    Reactor reactor;
    
    CommandManager cmd_manager(&reactor);

    ServerConsole server_console(STDIN_FILENO, &reactor);
    
    PluginLoader plugin_loader(&cmd_manager);
    Callback<PluginLoader, std::string> plugin_loader_callback(
        plugin_loader, 
        &PluginLoader::operator(), 
        &PluginLoader::OnDispatcherDeath);

    LoggerConfigurator logger_configurator;
    Callback<LoggerConfigurator, std::string> logger_configurator_callback(
        logger_configurator, 
        &LoggerConfigurator::operator(), 
        &LoggerConfigurator::OnDispatcherDeath);

    Dispatcher<std::string> dispatcher;
    dispatcher.Subscribe(&plugin_loader_callback);
    dispatcher.Subscribe(&logger_configurator_callback);

    UDPServer udp_server(NULL, atoi(argv[1]), cmd_manager, &reactor);
    udp_server.Init();

    // TCPServer tcp_server(NULL, atoi(argv[2]), cmd_manager, &reactor);
    // tcp_server.Init();

    std::string addons_dir("./add_ons/");
    DirMonitor dir_monitor(addons_dir, &reactor, &dispatcher);
    dir_monitor.Init();

    // tcp_server.AddToReactor();
    udp_server.AddToReactor();
    server_console.AddToReactor();
    dir_monitor.AddToReactor();


    reactor.Run();

    return 0;
}