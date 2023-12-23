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
    if (target != server.getClient(-1))
    {
        target.setSendBuffer(PRIVMSG(server.getHostname(), client.getNickname(), client.getUsername(), target.getNickname(), msg));
        return;
    }
    Channel &channel = server.getChannelByName(targetName);
    if (channel != server.getChannel(""))
    {
        channel.sendMessageToAllExcept(PRIVMSG(server.getHostname(), client.getNickname(), client.getUsername(), channel.getName(), msg), client);
        return;
    }
    client.setReplay(401, server);
}