#ifndef SERVERBASE_HPP
#define SERVERBASE_HPP

#include "terminal.hpp"
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>


class ServerBase : public Terminal{
    protected:
        int port;
        int server_fd;
        sockaddr_in server_address;
    public:
        ServerBase(int portno): port(portno){}
    
        void check(int stat,const std::string& msg);

        void bindToPort();
        void listenToClient(int max_client_number);
        void closeSocket(int sock);

        virtual void acceptValidConnection() = 0;
        virtual void handleClient() = 0;
        virtual std::string receiveFromClient() = 0;
        virtual void sendToClient(const std::string& transData) = 0;
        virtual void start() = 0;

        virtual ~ServerBase() = default;
};



#endif // SERVERBASE_HPP