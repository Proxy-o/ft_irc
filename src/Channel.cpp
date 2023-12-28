#include "Channel.hpp"
#include <ctime>
#include <cstdio>

Channel::Channel()
{
    this->_isInviteOnly = false;
    this->_isTopicSet = true;
    this->_topic = "";
}

Channel::Channel(Client *op, int op_fd)
{
    this->_chan_ops.insert(std::pair<int, Client *>(op_fd, op));
    this->_clients.insert(std::pair<int, Client *>(op_fd, op));
    this->_isInviteOnly = false;
    this->_isTopicSet = true;
    this->_topic = "";
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
    std::string modes = "+";
    if (this->_isInviteOnly)
        modes += "i";
    if (this->_isTopicSet)
        modes += "t";
    if (this->_password != "")
        modes += "k " + this->_password;
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

void Channel::setModes(std::string modes)
{
    if (modes.find("t") != std::string::npos)
        this->_isTopicSet = true;
    if (modes.find("i") != std::string::npos)
        this->_isInviteOnly = true;
    if (modes.find("k") != std::string::npos)
    {
        this->_password = modes.substr(modes.find("k") + 1);
    }

}
 