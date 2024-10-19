#include "terminal.hpp"
#include <iostream>
#include <string>

void Terminal::showTitle(const std::string &title)
{
    std::cout << BLUE << std::string(60,'-') << std::endl;
    std::cout << std::string(27,'-') << title << std::string(27,'-') << std::endl;
    std::cout << std::string(60,'-') << RESET << std::endl;
}

void Terminal::printMsg(const std::string &msg) {std::cout << WHITE << msg << RESET ; }

void Terminal::printErrorMsg(const std::string &msg) { std::cout << RED << msg << RESET ; }

void Terminal::printConnectMsg(const std::string &msg) { std::cout << GREEN << msg << RESET ; }

void Terminal::printConnectPort(const std::string &msg , int port) { std::cout << GREEN << msg << port << RESET << std::endl; }

void Terminal::printWarningMsg(const std::string &msg) { std::cout << YELLOW << msg << RESET ; }

void Terminal::printRecvMsg(const std::string &msg) { std::cout << MAGENTA << msg << RESET ; }

void Terminal::printSentMsg(const std::string &msg) { std::cout << BLUE << msg << RESET ; }


