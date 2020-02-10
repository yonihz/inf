// gd98 server_test.cpp server.cpp command.cpp ../thread/thread.cpp ../project/reactor/reactor.cpp ../project/reactor/fd_listener.cpp  ../socket/socket.cpp ../logger/logger.cpp -I../factory/ -I../logger/ -I../socket/ -I../waitable_queue/ -I../singleton/ -I../project/reactor/ -I../thread/ -pthread -lboost_system -o server.out


// with .so: 
// gd98 -c -fPIC command.cpp -o command.o
// gd98 -shared command.o -o libcommand.so
// gd98 server_test.cpp server.cpp ../thread/thread.cpp ../project/reactor/reactor.cpp ../project/reactor/fd_listener.cpp  ../socket/socket.cpp ../logger/logger.cpp -I../factory/ -I../logger/ -I../socket/ -I../waitable_queue/ -I../singleton/ -I../project/reactor/ -I../thread/ -pthread -lboost_system -Wl,-rpath,. -lcommand -L. -o server.out


#include <cstdlib>
#include <iostream>

#include "server.hpp"

using namespace ilrd;

int main(int argc, char *argv[])
{  
    if (argc != 3)
    {
        std::cout << "Error: need 2 ports as arguments to run" << std::endl;
        return 0;
    }

    Server server(atoi(argv[1]), atoi(argv[2])); // PORT_TCP, PORT_UDP
    server.Start();

    return 0;
}