#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sys/select.h>
#include <unistd.h>
#include "server.hpp"
#include "serverBase.hpp"
#include "terminal.hpp"
/* ---------------------------------------------------------------------------------------------------------------------------- */
/* ---------------Serever/client socket using TCP/IP as the network protocol and custom transmition protocol.------------------ */
/* ---------------------------------------------------------------------------------------------------------------------------- */

TCPServer::TCPServer(int port) : ServerBase(port) {
    Terminal::showTitle("SERVER");
    //[1] Creating socket file descriptor: AF_INET: IPV4 - SOCK_STREAM: TCP/IP
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(server_fd, "Socket Failed!\n");
}

void TCPServer::acceptValidConnection() {
    socklen_t addrlen = sizeof(server_address);
    new_socket = accept(server_fd, (struct sockaddr*)&server_address, &addrlen);
    check(new_socket, "ERROR: Accept failed!\n");
    printConnectMsg("Connected...!\n");
}

std::string TCPServer::receiveFromClient()
{
    // (1)-Clear buffer before receiving
    memset(recv_buffer.data(), 0, recv_buffer.size());

    // (2)-Receiving data from the client
    int recv_s = recv(new_socket, recv_buffer.data(), recv_buffer.size() - 1, 0);
    // (2)-(1) check receive status
    if (recv_s == 0) {
        printErrorMsg("Client disconnected!\n");
        return "exit";  // Return "exit" on failure or disconnect
    }else if(recv_s < 0){
        printErrorMsg("Receiving failed!\n");
        return "exit";
    }
    // (3)-Convert received data to string
    std::string request(recv_buffer.data(), recv_s);  
    return request;
}

void TCPServer::sendToClient(const std::string &transData) {
    send(new_socket, response.c_str(), response.size(), 0);
}

void TCPServer::handleClient() {
        while (true) {
        //receive
        std::string command = receiveFromClient();
        std::transform(command.begin(),command.end(),command.begin(),[](unsigned char c){return std::tolower(c);});        
        std::string response = command + " is opened!";
        if (command == "facebook"){
            printMsg("Openning facebook...\n");
            openFacebook();
        }else if (command == "whatsapp") {
            printMsg("Openning whatsapp...\n");
            openWhatsapp();
        }else if (command == "github") {
            printMsg("Openning github...\n");
            openGithub();
        }else if (command == "linkedin") {
            printMsg("Openning linkedin...\n");
            openLinkedin();
        }else if (command == "youtube") {
            printMsg("Openning youtube...\n");
            openYoutube();
        }else if (command == "calculator") {
            printMsg("Openning calculator...\n");
            openCalculator();
        }else if (command == "vscode") {
            printMsg("Openning vscode...\n");
            openVSCode();
        }else if (command == "telegram") {
            printMsg("Openning Telegram...\n");
            openTelegram();
        }else if (command == "exit") {
            printMsg("Exiting...\n");
            sendToClient("Exiting...");
            break;
        }else{
            printMsg("Unknown command\n");
            response = "Unknown command";
            // std::string response = command + " is failed";
            // sendToClient(response);
            // continue;    
        }

        // Send a response to the client
        sendToClient(response);

    }
}

void TCPServer::start() {
        //[1] bind to port
        bindToPort();

        //[2] listen for incoming connections
        listenToClient(1);

        //[3] accept a new connection
        acceptValidConnection();

        //[4] handle the client
        handleClient(); // Receive the command, process, and send a response

        //[5] close the connection with the current client
        closeSocket(server_fd);
}

TCPServer::~TCPServer() {
    closeSocket(server_fd);
}

/* ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------Serever/client socket using TCP/IP as the network protocol and http POST as transmition protocol.--------------- */
/* ---------------------------------------------------------------------------------------------------------------------------- */


TCPServerHttp::TCPServerHttp(int port) : ServerBase(port){
    Terminal::showTitle("SERVER");
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(server_fd, "Socket Failed!\n");   
}

void TCPServerHttp::acceptValidConnection() {
    socklen_t addrlen = sizeof(server_address);
    new_socket = accept(server_fd, (struct sockaddr*)&server_address, &addrlen);
    check(new_socket, "ERROR: Accept failed!\n");
    //printConnectMsg("Connected...!\n");
}

std::string TCPServerHttp::receiveFromClient() {
    memset(recv_buffer.data(), 0, recv_buffer.size());
    // Receiving data from the client
    int recv_s = recv(new_socket, recv_buffer.data(), recv_buffer.size() - 1, 0);
    if (recv_s <= 0) {
        //printErrorMsg(recv_s == 0 ? "Client disconnected!\n" : "Receiving failed!\n");
        return "break";  // Return "exit" on failure or disconnect
    }

    std::string request(recv_buffer.data(), recv_s);  // Convert received data to string
    //printWarningMsg("Raw HTTP Request: " + request + "\n");
    printRecvMsg(parsePost(request)+"\n");
    return parsePost(request);
}
std::string TCPServerHttp::parsePost(const std::string& request) {
    // Locate the body start (after headers)
    size_t body_start = request.find("\r\n\r\n");
    if (body_start != std::string::npos) {
        // Extract the body part (after "\r\n\r\n")
        std::string body = request.substr(body_start + 4);
        return body;
    }
    return request;
}
void TCPServerHttp::sendToClient(const std::string &transData) {
    // Send HTTP Response
        std::string response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/plain\r\n";
        response += "Content-Length: " + std::to_string(transData.size()) + "\r\n";
        response += "Connection: keep-alive\r\n"; // Keep the connection alive
        response += "\r\n"; // End of headers
        response += transData; // Add the actual response body
        
        send(new_socket, response.c_str(), response.size(), 0);
        printSentMsg("Response sent to client.\n");
}

void TCPServerHttp::handleClient() {
    while (true) {
        //receive
        std::string command = receiveFromClient();
        std::transform(command.begin(),command.end(),command.begin(),[](unsigned char c){return std::tolower(c);});   
        
        // Process the command and take action
        if (command == "facebook"){
            printMsg("Openning facebook...\n");
            openFacebook();
        }else if (command == "whatsapp") {
            printMsg("Openning whatsapp...\n");
            openWhatsapp();
        }else if (command == "github") {
            printMsg("Openning github...\n");
            openGithub();
        }else if (command == "linkedin") {
            printMsg("Openning linkedin...\n");
            openLinkedin();
        }else if (command == "youtube") {
            printMsg("Openning youtube...\n");
            openYoutube();
        }else if (command == "calculator") {
            printMsg("Openning calculator...\n");
            openCalculator();
        }else if (command == "vscode") {
            printMsg("Openning vscode...\n");
            openVSCode();
        }else if (command == "exit") {
            printMsg("exiting...\n");
            exit(EXIT_FAILURE);
        }
        else if (command == "break") {
            break;
        }else{
            //sendToClient(command);
            //continue;    
        }
        sendToClient(command);
    }
}

void TCPServerHttp::start() {
    bindToPort();
    while (true){
        listenToClient(1);
        acceptValidConnection();
        handleClient();
        closeSocket(new_socket);
    }

    closeSocket(server_fd);
}

TCPServerHttp::~TCPServerHttp() {
        closeSocket(server_fd);
}

/* ---------------------------------------------------------------------------------------------------------------------------- */
/* ----------Serever/multiple client socket using TCP/IP as the network protocol and custome transmition protocol.------------- */
/* ---------------------------------------------------------------------------------------------------------------------------- */

    TCPServerMClients::TCPServerMClients(int port) : ServerBase(port) {
        Terminal::showTitle("SERVER");
        //[1] Creating socket file descriptor: AF_INET: IPV4 - SOCK_STREAM: TCP/IP
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        check(server_fd, "Socket Failed!\n");
    }
    void TCPServerMClients::acceptValidConnection() {
        socklen_t addrlen = sizeof(server_address);
        new_socket = accept(server_fd, (struct sockaddr*)&server_address, &addrlen);
        check(new_socket, "ERROR: Accept failed!\n");
        std::cout << "Client #" << new_socket-3 << " " <<std::endl;
        printConnectMsg("Connected...!\n");
    }
    std::string TCPServerMClients::receiveFromClient() {
        memset(recv_buffer.data(), 0, recv_buffer.size());
        int recv_s = recv(new_socket, recv_buffer.data(), recv_buffer.size() - 1, 0);
        if (recv_s < 0) {
            printErrorMsg("Client disconnected!\n");
            return "exit"; 
        }else if(recv_s == 0){
            printErrorMsg("Receiving failed!\n");
            return "exit";
        }  
        return std::string(recv_buffer.data(), recv_s);
    }
    void TCPServerMClients::sendToClient(const std::string& transData) {
        send(new_socket, response.c_str(), response.size(), 0);
    }
    void TCPServerMClients::handleClient() {
        // Initialize the `select()` master set
        FD_ZERO(&master_set);
        FD_SET(server_fd, &master_set);
        max_sd = server_fd; // Start by tracking the server socket

        std::vector<int> client_sockets(MAX_CLIENT_NUMBER, 0); // Track client sockets

        while (true) {
            read_fds = master_set; // Copy the master set to read_fds (for select)

            // `select()` to monitor multiple sockets
            int activity = select(max_sd + 1, &read_fds, nullptr, nullptr, nullptr);
            if (activity < 0 && errno != EINTR) {
                perror("select error");
                exit(EXIT_FAILURE);
            }

            // If something happened on the server socket, it’s an incoming connection
            if (FD_ISSET(server_fd, &read_fds)) {
                acceptValidConnection();

                // Add new socket to the client_sockets list
                for (int &client_socket : client_sockets) {
                    if (client_socket == 0) {
                        client_socket = new_socket; // Assign the new socket
                        FD_SET(new_socket, &master_set); // Add to the master set
                        if (new_socket > max_sd) max_sd = new_socket; // Update max_sd
                        break;
                    }
                }
            }

            // Check all client sockets for incoming data
            for (int &client_socket : client_sockets) {
                if (FD_ISSET(client_socket, &read_fds)) {
                    // Clear buffer and receive data
                    memset(recv_buffer.data(), 0, recv_buffer.size());
                    int valread = recv(client_socket, recv_buffer.data(), RECV_BUFFER_SIZE, 0);

                    if (valread == 0) {
                        printErrorMsg("Client disconnected!\n");
                        close(client_socket);
                        FD_CLR(client_socket, &master_set); // Remove socket from master set
                        client_socket = 0; // Mark socket as available
                    } else {
                        // Process client command
                        std::string command(recv_buffer.data(), valread);
                        printRecvMsg("Command received: " + command + "\n");
                        // Convert the command to lowercase
                        std::transform(command.begin(), command.end(), command.begin(),
                                    [](unsigned char c) { return std::tolower(c); });
                        if (command == "facebook") {
                            std::string response = "Opening Facebook...";
                            printMsg("Openning Facebook...\n");
                            openFacebook();
                            send(client_socket, response.c_str(), response.size(), 0);
                        }else if (command == "youtube") {
                            std::string response = "Opening youtube...";
                            printMsg("Openning youtube...\n");
                            openYoutube();
                            send(client_socket, response.c_str(), response.size(), 0);
                        }else if (command == "telegram") {
                            std::string response = "Opening telegram...";
                            printMsg("Openning telegram...\n");
                            openTelegram();
                            send(client_socket, response.c_str(), response.size(), 0);
                        }else if (command == "whatsapp") {
                            std::string response = "Opening whatsapp...";
                            printMsg("Openning Whatsapp...\n");
                            openWhatsapp();
                            send(client_socket, response.c_str(), response.size(), 0);
                        }else if (command == "github") {
                            std::string response = "Opening github...";
                            printMsg("Openning github...\n");
                            openGithub();
                            send(client_socket, response.c_str(), response.size(), 0);
                        }else if (command == "linkedin") {
                            std::string response = "Opening linkedin...";
                            printMsg("Openning linkedin...\n");
                            openLinkedin();
                            send(client_socket, response.c_str(), response.size(), 0);
                        }else if (command == "calc") {
                            std::string response = "Opening calculator...";
                            printMsg("Openning calculator...\n");
                            openCalculator();
                            send(client_socket, response.c_str(), response.size(), 0);
                        }else if (command == "vscode") {
                            std::string response = "Opening vscode...";
                            printMsg("Openning vscode...\n");
                            openVSCode();
                            send(client_socket, response.c_str(), response.size(), 0);
                        }else if (command == "exit") {
                            std::string response = "Exiting...";
                            printMsg("Exiting...\n");
                            send(client_socket, response.c_str(), response.size(), 0);
                            close(client_socket);
                            FD_CLR(client_socket, &master_set); // Remove socket from master set
                            client_socket = 0; // Mark socket as available
                        } else {
                            std::string response = "Unknown command";
                            send(client_socket, response.c_str(), response.size(), 0);
                        }
                    }
                }
            }
        }
    }
    void TCPServerMClients::start() {
        bindToPort();

        listenToClient(MAX_CLIENT_NUMBER);
    
        handleClient();
    }

    TCPServerMClients::~TCPServerMClients() {
        closeSocket(server_fd);
    }
