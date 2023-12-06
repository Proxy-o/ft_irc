#pragma once

#include <sys/types.h>
#include <iostream>

class Client
{
private:
    std::string _username;
    std::string _realname;
    std::string _nickname;
    int _client_sockfd;
    std::string _recv_buffer;
    std::string _send_buffer;
    bool _is_registered;

public:
    Client(int sockfd);
    ~Client();
    Client &operator=(const Client &client);
    bool operator==(const Client &client) const;
    bool operator!=(const Client &client) const;
    // ************SETTERS************
    void setRecvBuffer(std::string buffer);
    void setIsRegistered(bool status);
    void setSendBuffer(std::string buffer);
    void setNickname(std::string nickname);
    void setUsername(std::string username);
    void setRealname(std::string realname);

    // ************GETTERS************
    std::string getRecvBuffer();
    bool isRegistered();
    std::string getSendBuffer();
    std::string getNickname();
    std::string getUsername();
    std::string getRealname();

    // ************METHODS************
    void resetRecvBuffer();
    void resetSendBuffer();

};

