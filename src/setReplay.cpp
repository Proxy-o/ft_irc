#include "Client.hpp"

void Client::setReplay(int replay)
{
    std::string message;
    Client &client = *this;
    Server &server = client.getServer();
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