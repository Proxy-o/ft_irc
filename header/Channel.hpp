#pragma once

#include <sys/types.h>
#include <iostream>
#include "Server.hpp"
#include "Client.hpp"
#include "irc_replies.hpp"

class Client;
class Server;
class Channel
{
private:
    std::map<int, Client &> _clients;
    std::map<int, Client &> _chan_ops;
    std::string _topic;
    std::string _name;
    std::string _password;
    bool _isPrivate;
    bool _isSecret;
    bool _isInviteOnly;


public:
    Channel();
    Channel(Client *op, int op_fd);
    ~Channel();
    // ************SETTERS************
    void setOperator(Client *op, int op_fd);
    void setTopic(std::string topic);
    void setName(std::string name);
    void setPassword(std::string password);
    void setIsPrivate(bool status);
    void setIsSecret(bool status);
    void setIsInviteOnly(bool status);

    // ************GETTERS************
    std::string getTopic();
    std::string getName();
    std::string getPassword();
    std::string getModes();
    bool isPrivate();
    bool isSecret();
    bool isInviteOnly();

    // ************METHODS************
    void addClient(Client &client);
    void removeClient(Client &client);
    void sendMessageToAll(std::string message);
    void setReplay(int replay, Server &server, Client &client);
};
