#include "server.hpp"
#include <cstring>

int main(int argc, char const *argv[]) {
    const int portNumber = 8080;
    TCPServerMClients tcpserver(portNumber);
    tcpserver.start();
    return 0;
}
