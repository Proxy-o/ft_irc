#pragma once

#include <sys/types.h>
#include <iostream>

class Client
{
private:
    std::string _username;
    std::string _nickname;
    int _client_sockfd;
    std::string _recv_buffer;
    bool _is_registered;

public:
    Client(int sockfd);
    ~Client();
    // ************SETTERS************
    void setRecvBuffer(std::string buffer);
    void setIsRegistered(bool status);

    // ************GETTERS************
    std::string getRecvBuffer();
    bool isRegistered();

    // ************METHODS************
    void resetRecvBuffer();

};

