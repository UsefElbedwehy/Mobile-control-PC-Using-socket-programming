#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../terminal.hpp"
#include <array>

class Client : public Terminal
{
private:
    static const int SEND_BUFFER_SIZE = 100;
    static const int RECV_BUFFER_SIZE = 100;
    std::array<char, RECV_BUFFER_SIZE> recv_buffer{};
    std::string sbuffer{};
    std::string ip_address;
    int port;
    int client_df;
    
public:
    void connectToServer();
    void sendMsg(const std::string& msg);
    std::string recvMsg();
    Client(const std::string& IP, int port_number);
    ~Client();
};

#endif // !CLIENT_HPP