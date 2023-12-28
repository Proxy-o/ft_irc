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
    if (tokens[2].find(":") == 0)
    {
        msg = message.substr(message.find(":") );
    }
    else
    {
        msg = tokens[2];
    }
    Client &target = server.getClientByNickname(targetName);
    
    if (target != server.getClient(-1))
    {
        if (target.isRegistered() == false)
        {
            client.setSendBuffer(ERR_NOSUCHNICK(server.getHostname(), client.getNickname(), targetName));
            return;
        }
        target.setSendBuffer(PRIVMSG(client.getHostname(), client.getNickname(), client.getUsername(), target.getNickname(), msg));
        return;
    }
    Channel &channel = server.getChannelByName(targetName);
    if (channel != server.getChannel(""))
    {
        if (!channel.clientExist(client))
        {
            client.setReplay(404, server);
            return;
        }
        channel.sendMessageToAllExcept(PRIVMSG(server.getHostname(), client.getNickname(), client.getUsername(), channel.getName(), msg), client);
        return;
    }
    client.setSendBuffer(ERR_NOSUCHNICK(server.getHostname(), client.getNickname(), targetName));
}