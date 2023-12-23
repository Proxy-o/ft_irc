#include "Channel.hpp"

Channel::Channel()
{
    this->_isPrivate = false;
    this->_isSecret = false;
    this->_isInviteOnly = false;
}

Channel::Channel(Client *op, int op_fd)
{
    this->_chan_ops.insert(std::pair<int, Client &>(op_fd, *op));
    this->_isPrivate = false;
    this->_isSecret = false;
    this->_isInviteOnly = false;
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
    this->_isPrivate = channel._isPrivate;
    this->_isSecret = channel._isSecret;
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
    this->_chan_ops.insert(std::pair<int, Client &>(op_fd, *op));
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

void Channel::setIsPrivate(bool status)
{
    this->_isPrivate = status;
}

void Channel::setIsSecret(bool status)
{
    this->_isSecret = status;
}

void Channel::setIsInviteOnly(bool status)
{
    this->_isInviteOnly = status;
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
    std::string modes = "nt";
    if (this->_isPrivate)
        modes += "p";
    if (this->_isSecret)
        modes += "s";
    if (this->_isInviteOnly)
        modes += "i";
    return (modes);
}

bool Channel::isPrivate()
{
    return (this->_isPrivate);
}

bool Channel::isSecret()
{
    return (this->_isSecret);
}

bool Channel::isInviteOnly()
{
    return (this->_isInviteOnly);
}

std::map<int, Client &> &Channel::getClients()
{
    return (this->_clients);
}

std::map<int, Client &> &Channel::getChanOps()
{
    return (this->_chan_ops);
}

// ************METHODS************

void Channel::addClient(Client &client)
{
    this->_clients.insert(std::pair<int, Client &>(client.getClientSockfd(), client));
}

void Channel::addop(Client &client)
{
    this->_chan_ops.insert(std::pair<int, Client &>(client.getClientSockfd(), client));
}

std::string Channel::isOp(Client &client)
{
    std::map<int, Client &>::iterator it = this->_chan_ops.begin();
    for (; it != this->_chan_ops.end(); it++)
    {
        if (it->second == client)
            return ("@");
    }
    return ("");
}

void Channel::removeClient(Client &client)
{
    this->_clients.erase(client.getClientSockfd());
}

void Channel::sendMessageToAll(std::string message)
{
    std::map<int, Client &>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        PRINT("SENDING TO: " + it->second.getNickname());
        it->second.setSendBuffer(message);
    }
}

void Channel::sendMessageToAllExcept(std::string message, Client &client)
{
    std::map<int, Client &>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        if (it->second == client)
            continue;
        it->second.setSendBuffer(message);
    }
}

bool Channel::clientExist(Client &client)
{
    std::map<int, Client &>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        if (it->second == client)
            return (true);
    }
    return (false);
}
