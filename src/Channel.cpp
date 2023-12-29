#include "Channel.hpp"
#include <ctime>
#include <cstdio>

Channel::Channel()
{
    this->_isInviteOnly = false;
    this->_topic = "";
    this->_clients_limit = 0;
    this->_isTopic = true;
}

Channel::Channel(Client *op, int op_fd)
{
    this->_chan_ops.insert(std::pair<int, Client *>(op_fd, op));
    this->_clients.insert(std::pair<int, Client *>(op_fd, op));
    this->_isInviteOnly = false;
    this->_topic = "";
    this->_isTopic = true;
    this->_clients_limit = 0;
}

Channel::~Channel()
{
}

Channel &Channel::operator=(const Channel &channel)
{
    this->_clients = channel._clients;
    this->_chan_ops = channel._chan_ops;
    this->_topic = channel._topic;
    this->_name = channel._name;
    this->_password = channel._password;
    this->_isInviteOnly = channel._isInviteOnly;
    return (*this);
}

bool Channel::operator==(const Channel &channel) const
{
    return (this == &channel);
}

bool Channel::operator!=(const Channel &channel) const
{
    return !(*this == channel);
}
// ************SETTERS************
void Channel::setOperator(Client *op, int op_fd)
{
    this->_chan_ops.insert(std::pair<int, Client *>(op_fd, op));
}

void Channel::setTopic(std::string topic)
{
    this->_topic = topic;
}

void Channel::setName(std::string name)
{
    this->_name = name;
}

void Channel::setPassword(std::string password)
{
    this->_password = password;
}

void Channel::setIsInviteOnly(bool status)
{
    this->_isInviteOnly = status;
}

void Channel::setClientsLimit(int limit)
{
    this->_clients_limit = limit;
}

void Channel::setIsTopic(bool status)
{
    this->_isTopic = status;
}

// ************GETTERS************


std::string Channel::getTopic()
{
    return (this->_topic);
}

std::string Channel::getName()
{
    return (this->_name);
}

std::string Channel::getPassword()
{
    return (this->_password);
}

std::string Channel::getModes()
{
    std::string modes = "";
    if (this->_isInviteOnly)
        modes += "i";
    if (this->_isTopic)
        modes += "t";
    if (this->_password != "")
        modes += "k";
    if (this->_clients_limit > 0)
        modes += "l";
    if (this->_password != "")
        modes += " " + this->_password;
    if (this->_clients_limit > 0)
        modes += " " + std::to_string(this->_clients_limit);
    if (modes.length())
        modes = "+" + modes;
    return (modes);
}

bool Channel::isInviteOnly()
{
    return (this->_isInviteOnly);
}

std::map<int, Client *> &Channel::getClients()
{
    return (this->_clients);
}

std::map<int, Client *> &Channel::getChanOps()
{
    return (this->_chan_ops);
}

int Channel::getClientsLimit()
{
    return (this->_clients_limit);
}

bool Channel::isTopic()
{
    return (this->_isTopic);
}

std::map<int, Client *> &Channel::getInvitedClients()
{
    return (this->_invited_clients);
}

// ************METHODS************

void Channel::addClient(Client &client)
{
    this->_clients.insert(std::pair<int, Client *>(client.getClientSockfd(), &client));
}

void Channel::addop(Client &client)
{
    this->_chan_ops.insert(std::pair<int, Client *>(client.getClientSockfd(), &client));
}

std::string Channel::isOp(Client &client)
{
    std::map<int, Client *>::iterator it = this->_chan_ops.begin();
    for (; it != this->_chan_ops.end(); it++)
    {
        if (it->second->getNickname() == client.getNickname())
            return ("@");
    }
    return ("");
}

void Channel::removeClient(Client &client)
{
    this->_clients.erase(client.getClientSockfd());
    if (this->isOp(client) == "@")
        this->_chan_ops.erase(client.getClientSockfd());
}

void Channel::sendMessageToAll(std::string message)
{
    std::map<int, Client *>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        it->second->setSendBuffer(message);
    }
}

void Channel::sendMessageToAllExcept(std::string message, Client &client)
{
    std::map<int, Client *>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        if (it->second->getNickname() == client.getNickname())
            continue;
        it->second->setSendBuffer(message);
    }
}

bool Channel::clientExist(Client &client)
{
    std::map<int, Client *>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        if (it->second->getNickname() == client.getNickname())
            return (true);
    }
    return (false);
}


void Channel::setTopicSetter(Client &setter)
{
    std::string setter_name = setter.getNickname() + "!" + setter.getUsername() + "@" + setter.getHostname();
    this->_topic_setter = setter_name;

}


void Channel::setTopicDate()
{
    std::time_t currentTime = std::time(NULL);
    // Convert the time to string using sprintf
    char buffer[20];  // Adjust the size accordingly
    std::sprintf(buffer, "%ld", static_cast<long>(currentTime));

    this->_topic_date = buffer;
}

std::string Channel::getTopicSetter()
{
    return (this->_topic_setter);
}

std::string Channel::getTopicDate()
{
    return (this->_topic_date);
}

void Channel::removeOp(Client &client)
{
    this->_chan_ops.erase(client.getClientSockfd());
}



Client *Channel::getClientByNickname(std::string nickname)
{
    std::map<int, Client *>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        if (it->second->getNickname() == nickname)
            return (it->second);
    }
    return (NULL);
}

bool Channel::isInvited(Client &client)
{
    if (this->_invited_clients.size() == 0)
        return (false);
    std::map<int, Client *>::iterator it = this->_invited_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        if (it->second->getNickname() == client.getNickname())
            return (true);
    }
    return (false);
}