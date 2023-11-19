#pragma once

#include <sys/types.h>
#include <iostream>

class Client
{
private:
    std::string _username;
    std::string _nickname;
    int _client_sockfd;

public:
    Client(int sockfd);
    ~Client();
};
