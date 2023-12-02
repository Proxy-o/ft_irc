#pragma once

#include <sys/types.h>
#include <iostream>

class Client
{
private:
    std::string _username;
    std::string _nickname;
    int _client_sockfd;
    std::string _buffer;

public:
    Client(int sockfd);
    ~Client();
    // ************SETTERS************
    void setBuffer(std::string buffer);

    // ************GETTERS************
    std::string getBuffer();

};

