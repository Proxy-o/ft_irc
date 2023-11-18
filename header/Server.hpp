#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define PRINT(x) std::cout << x << std::endl;
#define PRINT_ERR(x) std::cerr << x << std::endl;
#define SUCCESS 0
#define FAILURE -1
// colors
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

class Server
{
private:
    std::string _creation_date;
    std::string _password;
    std::string _port;
    int _serv_sockfd;
    struct addrinfo *_serv_info;

public:
    Server(std::string password, std::string port);
    ~Server();
    int networkInit();
    // ************SETTERS************
    void setCreationDate();

    // ************GETTERS************
    std::string getCreationDate();
    struct addrinfo *getServInfo();
};
