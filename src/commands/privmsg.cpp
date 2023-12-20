#include "commands.hpp"

void privmsg(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> tokens = ft_split(message, " ");
    if (tokens.size() < 3)
    {
        client.setReplay(461, server);
        return;
    }
    std::string targetName = tokens[1];
    std::string msg;
    // find in the message the first occurence of ":"
    std::size_t pos = message.find(":");
    if (pos != std::string::npos)
    {
        msg = message.substr(pos);
    }
    else
    {
        msg = tokens[2];
    }
    Client &target = server.getClientByNickname(targetName);
    if (target == server.getClient(-1))
    {
        client.setReplay(401);

        return;
    }
    target.setSendBuffer(PRIVMSG(server.getHostname(), client.getNickname(), client.getUsername(), target.getNickname(), msg));
}