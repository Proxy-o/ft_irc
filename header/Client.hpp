#pragma once

#include <sys/types.h>
#include <iostream>
#include "Server.hpp"

class Server;
class Client
{
private:
    std::string _username;
    std::string _realname;
    std::string _nickname;
    std::string _hostname;
    int _client_sockfd;
    std::string _recv_buffer;
    std::string _send_buffer;
    bool _is_registered;
    bool _pass_is_correct;
    bool _is_welcomed;
    bool is_operator;

public:
    Client();
    Client(int sockfd, sockaddr_storage client_addr);
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
    void setIsPassCorrect(bool status);
    void setIsWelcomed(bool status);
    void setIsOperator(bool status);

    // ************GETTERS************
    std::string getRecvBuffer();
    bool isRegistered();
    std::string getSendBuffer();
    std::string getNickname();
    std::string getUsername();
    std::string getRealname();
    std::string getHostname();
    bool isPassCorrect();
    bool isWelcomed();
    bool isOperator();
    int getClientSockfd();

    // ************METHODS************
    void resetRecvBuffer();
    void resetSendBuffer();
    void setReplay(int replay, Server &server);
    std::string getClientHostname(sockaddr_storage* addr);

};
