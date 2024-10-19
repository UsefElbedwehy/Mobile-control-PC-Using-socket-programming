#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "client.hpp"
#include "../terminal.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>  // For inet_pton


Client::Client(const std::string& IP, int port_number) : ip_address(IP),port(port_number){
    //[1] create socket
    Terminal::showTitle("CLIENT");
    client_df = socket(AF_INET, SOCK_STREAM, 0);
    if(client_df < 0){
        printErrorMsg("Error: socket failed!");
        exit(EXIT_FAILURE);
    }
    connectToServer();
}

void Client::connectToServer() {
    //[2] connect to the server
    sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(port); 
    inet_pton(AF_INET, ip_address.c_str(), &client_address.sin_addr);
    int connect_s = connect(client_df, (struct sockaddr*)&client_address, sizeof(client_address));
    if(connect_s < 0){
        printErrorMsg("Error: Connect failed!");
        exit(EXIT_FAILURE);
    }
    //connected   
    printConnectPort("Connected to "+ip_address , port);
}

void Client::sendMsg(const std::string &msg)
{
    int send_s = send(client_df, msg.data(), msg.size(),0);
    printSentMsg("Sending to the server: "+ msg +"\n");
}

std::string Client::recvMsg()
{
    memset(recv_buffer.data(), 0,recv_buffer.size());
    //[4]receive a response
    int recv_s = recv(client_df, recv_buffer.data(), RECV_BUFFER_SIZE, 0);
    if(recv_s < 0){
        printErrorMsg("Error: Receiving failed!");
        return "";
    }
    return std::string(recv_buffer.data());
}

Client::~Client()
{
    //[5] Close the client socket 
    printMsg("Socket closed!\n");
    close(client_df);
}

#endif // !TERMINAL_HPP