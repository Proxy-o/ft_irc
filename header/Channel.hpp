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
    std::map<int, Client *> _clients;
    std::map<int, Client *> _chan_ops;
    std::string _topic;
    std::string _topic_setter;
    std::string _topic_date;
    std::string _name;
    std::string _password;
    bool _isTopicSet;
    bool _isInviteOnly;


public:
    Channel();
    Channel(Client *op, int op_fd);
    ~Channel();
    Channel &operator=(const Channel &channel);
    bool operator==(const Channel &channel) const;
    bool operator!=(const Channel &channel) const;

    // ************SETTERS************
    void setOperator(Client *op, int op_fd);
    void setTopic(std::string topic);
    void setName(std::string name);
    void setPassword(std::string password);
    void setIsPrivate(bool status);
    void setIsSecret(bool status);
    void setIsInviteOnly(bool status);
    void setTopicSetter(Client &client);
    void setTopicDate();
    void setModes(std::string modes);

    // ************GETTERS************
    std::string getTopic();
    std::string getName();
    std::string getPassword();
    std::string getModes();
    Channel &getChannelByName(std::string name);
    bool isPrivate();
    bool isSecret();
    bool isInviteOnly();
    std::map<int, Client *> &getClients();
    std::map<int, Client *> &getChanOps();
    std::string getTopicSetter();
    std::string getTopicDate();

    // ************METHODS************
    void addClient(Client &client);
    void addop(Client &client);
    std::string isOp(Client &client);
    void removeClient(Client &client);
    void sendMessageToAll(std::string message);
    void sendMessageToAllExcept(std::string message, Client &client);
    void setReplay(int replay, Server &server, Client &client);
    bool clientExist(Client &client);
    void removeOp(Client &client);
};
