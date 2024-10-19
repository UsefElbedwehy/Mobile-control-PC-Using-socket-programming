#ifndef SERVER_HPP
#define SERVER_HPP

#include "commands.hpp"
#include "serverBase.hpp"
#include <array>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>

/* ---------------------------------------------------------------------------------------------------------------------------- */
/* ---------------Serever/client socket using TCP/IP as the network protocol and custom transmition protocol.------------------ */
/* ---------------------------------------------------------------------------------------------------------------------------- */


class TCPServer : public ServerBase , private Commands
{
private:
    int new_socket;
    static const int RECV_BUFFER_SIZE = 1024;
    std::array<char, RECV_BUFFER_SIZE> recv_buffer{};
    std::string response = "Msg Received!";
public:
    TCPServer(int port);
    void acceptValidConnection() override;
    std::string receiveFromClient() override;
    void sendToClient(const std::string& transData) override;
    void handleClient() override;
    void start() override;


    ~TCPServer();
};

/* ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------Serever/client socket using TCP/IP as the network protocol and http POST as transmition protocol.--------------- */
/* ---------------------------------------------------------------------------------------------------------------------------- */

class TCPServerHttp : public ServerBase , private Commands
{
private:
    int new_socket;
    static const int RECV_BUFFER_SIZE = 1024;
    std::array<char, RECV_BUFFER_SIZE> recv_buffer{};
    std::string response = "Msg Received!";
    std::string parsePost(const std::string& request);
public:
    TCPServerHttp(int port);
    void acceptValidConnection() override;
    std::string receiveFromClient() override;
    void sendToClient(const std::string& transData) override;
    void handleClient() override;
    void start() override;


    ~TCPServerHttp();
};

/* ---------------------------------------------------------------------------------------------------------------------------- */
/* ----------Serever/multiple client socket using TCP/IP as the network protocol and custome transmition protocol.------------- */
/* ---------------------------------------------------------------------------------------------------------------------------- */

class TCPServerMClients : public ServerBase , private Commands
{
private:
    static const int MAX_CLIENT_NUMBER = 64;
    static const int RECV_BUFFER_SIZE = 1024;
    std::array<char, RECV_BUFFER_SIZE> recv_buffer{};
    std::string response = "Msg Received!";
    int new_socket;
    fd_set master_set , read_fds;  // master set and temp set for `select()`
    int max_sd;     // Maximum socket descriptor
public:
    TCPServerMClients(int port);
    void acceptValidConnection() override;
    std::string receiveFromClient() override;
    void sendToClient(const std::string& transData) override;
    void handleClient() override;
    void start() override;


    ~TCPServerMClients();
};


#endif // SERVER_HPP