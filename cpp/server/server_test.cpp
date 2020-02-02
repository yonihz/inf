// gd98 server_test.cpp server.cpp socket.cpp ../logger/logger.cpp -I../logger/ -pthread -D_POSIX_C_SOURCE=200112L -o server.out

#include "server.hpp"

#define UNUSED(x) (void)(x)

#define PORT_TCP "5551"
#define PORT_UDP "5552"
#define PORT_BC "5553"

int main(int argc, char *argv[])
{  
    UNUSED(argc);
    UNUSED(argv[0]);

    CreateServer(PORT_TCP, PORT_UDP, PORT_BC);

    return 0;
}