#include "commands.hpp"
#include "Server.hpp"

static bool nickIsValid(std::string nickname)
{
    if (nickname.find_first_of(" ,.@?!*") != std::string::npos)
        return false;
    if (nickname.find_first_of("123456789$:#") == 0)
        return false;
    else
        return true;
}

void nick(std::string &message, Client &client, Server &server)
{

    std::vector<std::string> tokens = ft_split(message, " ");

    if (tokens.size() < 2)
    {
        client.setSendBuffer(ERR_NONICKNAMEGIVEN(client.getNickname()));
        return;
    }
    std::string nickname = tokens[1];
    if (nickIsValid(nickname) == false)
    {
        client.setSendBuffer(ERR_ERRONEUSNICKNAME(client.getNickname(), nickname));
        return;
    }

    Client &old_client = server.getClientByNickname(nickname);
    if (old_client != server.getClient(-1) && old_client != client)
    {
        client.setSendBuffer(ERR_NICKNAMEINUSE(client.getNickname(), nickname));
        return;
    }
    client.setSendBuffer(RPL_NICK(client.getNickname(), client.getUsername(), nickname));
    client.setNickname(nickname);
}