// gd98 server_test.cpp server.cpp ../socket/socket.cpp ../thread/thread.cpp ../logger/logger.cpp -I../logger/ -I../socket/ -I../thread/ -pthread -I../waitable_queue/ -o server.out

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

    CreateServer(atoi(argv[1]), atoi(argv[2])); // PORT_TCP, PORT_UDP

    return 0;
}