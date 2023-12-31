#include "commands.hpp"
#include "Server.hpp"

static bool nickIsValid(std::string nickname)
{
    if (nickname.find_first_of(",.@?!*") != std::string::npos)
        return false;
    if (nickname.find_first_of("123456789$:#&") == 0)
        return false;
    else
        return true;
}

void nick(std::string &message, Client &client, Server &server)
{

    std::vector<std::string> tokens = ft_split(message, " ");

    if (tokens.size() < 2)
    {
        client.setSendBuffer(ERR_NONICKNAMEGIVEN(server.getHostname(), client.getNickname()));
        return;
    }
    std::string nickname = tokens[1];
    if (nickIsValid(nickname) == false)
    {

        client.setSendBuffer(ERR_ERRONEUSNICKNAME(server.getHostname(), client.getNickname(), nickname));
        return;
    }

    Client &old_client = server.getClientByNickname(nickname);
    if (old_client != server.getClient(-1) && old_client != client)
    {
        std::string old_nickname = client.getNickname();
        old_nickname == "" ? old_nickname = "*" : old_nickname;
        client.setSendBuffer(ERR_NICKNAMEINUSE(server.getHostname(), old_nickname, nickname));
        return;
    }
    std::string nick_to_send;
    if (client.getNickname() == "*" || client.getNickname() == "")
        nick_to_send = nickname;
    else
        nick_to_send = client.getNickname();
    client.setSendBuffer(RPL_NICK(client.getHostname(), nick_to_send, client.getUsername(), nickname));
    client.setNickname(nickname);
}