#include "client.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    Client client1("192.168.1.11",8080);

    std::string response("");
    std::string msg;
    while (msg != "exit") {
        std::getline(std::cin,msg);
        client1.sendMsg(msg);
        response = client1.recvMsg();
        std::cout << "Server response: " << response << std::endl;
    }
    
    
    return 0;
}
