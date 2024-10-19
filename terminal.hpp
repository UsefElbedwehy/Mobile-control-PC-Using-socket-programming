#ifndef TERMINALL_HPP
#define TERMINALL_HPP

#include <string>

class Terminal
{
protected:
    // ANSI escape codes for colors
    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string RESET = "\033[0m";
    void showTitle(const std::string &title);
    void printErrorMsg(const std::string &msg);
    void printConnectMsg(const std::string &msg);
    void printConnectPort(const std::string &msg , int port);
    void printWarningMsg(const std::string &msg);
    void printRecvMsg(const std::string &msg);
    void printSentMsg(const std::string &msg);
    void printMsg(const std::string &msg);
public:
};


#endif