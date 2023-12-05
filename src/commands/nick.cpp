#include "commands.hpp"
#include "Server.hpp"

static bool	nickIsValid(std::string nickname)
{
    if (nickname.find_first_of(" ,.@?!*") != std::string::npos)
        return false;
    if (nickname.find_first_of("123456789$:#") == 0)
        return false;
    else
    return true;
}

void nick(std::vector<std::string> &message, Client &client, Server &server)
{
    (void)server;
    if (message.size() < 2)
    {
        client.setSendBuffer(ERR_NONICKNAMEGIVEN(client.getNickname()));
        return;
    }
    std::string nickname = message[1];
    if (nickIsValid(nickname) == false)
    {
        client.setSendBuffer(ERR_ERRONEUSNICKNAME(client.getNickname(), nickname));
        return;
    }
    // if (nickname.size() > 9)
    // {
    //     client.sendReply(ERR_NICKNAMEINUSE, nickname + ":Nickname is already in use");
    //     return;
    // }
    // if (server.getClientByNickname(nickname) != NULL)
    // {
    //     client.sendReply(ERR_NICKNAMEINUSE, nickname + ":Nickname is already in use");
    //     return;
    // }
    // client.setNickname(nickname);
    // if (client.isRegistered() == false)
    // {
    //     client.setRegistered(true);
    //     client.sendReply(RPL_WELCOME, ":Welcome to the Internet Relay Network " + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname());
    //     client.sendReply(RPL_YOURHOST, ":Your host is " + server.getHostname() + ", running version 1.0");
    //     client.sendReply(RPL_CREATED, ":This server was created " + server.getCreationDate());
    //     client.sendReply(RPL_MYINFO, server.getHostname() + " 1.0 o o");
    // }
    // else
    // {
    //     client.sendReply(RPL_NICK, client.getNickname());
    // }
}