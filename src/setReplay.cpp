#include "Client.hpp"
#include "Channel.hpp"

void Client::setReplay(int replay, Server &server)
{
    std::string message;
    Client &client = *this;
    switch (replay)
    {
    case 001:
        message = RPL_WELCOME(server.getHostname(), client.getNickname());
        break;
    case 002:
        message = RPL_YOURHOST(server.getHostname(), client.getNickname());
        break;
    case 003:
        message = RPL_CREATED(server.getHostname(), client.getNickname(), server.getCreationDate());
        break;
    case 004:
        message = RPL_MYINFO(server.getHostname(), client.getNickname());
        break;
    case 005:
        message = RPL_ISUPPORT(server.getHostname(), client.getNickname());
        break;
    case 381:
        message = RPL_YOUREOPER(server.getHostname(), client.getNickname());
        break;
    case 401:
        message = ERR_NOSUCHNICK(server.getHostname(), client.getNickname(), client.getNickname());
        break;
    case 404:
        message = ERR_CANNOTSENDTOCHAN(server.getHostname(), client.getNickname(), client.getNickname());
        break;
    case 431:
        message = ERR_NONICKNAMEGIVEN(server.getHostname(), client.getNickname());
        break;
    case 461:
        message = ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "USER");
        break;
    case 462:
        message = ERR_ALREADYREGISTERED(server.getHostname(), client.getNickname());
        break;
    case 464:
        message = ERR_PASSWDMISMATCH(server.getHostname(), client.getNickname());
        break;
    default:
        message = "NOT IMPLEMENTED YET\r\n";
        break;
    }
    client.setSendBuffer(message);
}
void Channel::setReplay(int replay, Server &server, Client &client)
{
    std::string message = "";
    switch (replay)
    {
    case 403:
        message = ERR_NOSUCHCHANNEL(server.getHostname(), client.getNickname(),this->getName());
        break;
    case 101:
        message = RPL_MODE(server.getHostname(), this->getName(), "+" + this->getModes());
        break;
    case 102:
        message = ERR_USERONCHANNEL(server.getHostname(), client.getUsername(), client.getNickname(), this->getName());
        break;
    case 366:
        message = RPL_ENDOFNAMES(server.getHostname(), client.getNickname(), this->getName());
        break;
    case 332:
        message = RPL_TOPIC(server.getHostname(), client.getNickname(), this->getName(), this->getTopic());
        break;
    case 333:
        message = RPL_TOPICWHOTIME(server.getHostname(), client.getNickname(), this->getName(), this->getTopicSetter(), this->getTopicDate());
        break;
    default:
        message = "NOT IMPLEMENTED YET\r\n";
        break;
    }
    client.setSendBuffer(message);
}
