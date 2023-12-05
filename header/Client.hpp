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
    std::string _send_buffer;
    bool _is_registered;

public:
    Client(int sockfd);
    ~Client();
    // ************SETTERS************
    void setRecvBuffer(std::string buffer);
    void setIsRegistered(bool status);
    void setSendBuffer(std::string buffer);
    void setNickname(std::string nickname);

    // ************GETTERS************
    std::string getRecvBuffer();
    bool isRegistered();
    std::string getSendBuffer();
    std::string getNickname();

    // ************METHODS************
    void resetRecvBuffer();
    void resetSendBuffer();

};

