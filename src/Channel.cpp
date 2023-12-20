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

// ************METHODS************

void Channel::addClient(Client &client)
{
    this->_clients.insert(std::pair<int, Client &>(client.getClientSockfd(), client));
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
        it->second.setSendBuffer(message);
    }
}
