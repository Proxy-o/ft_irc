#include "commands.hpp"

void part(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> tokens = ft_split(message, " ");

    if (tokens.size() < 2)
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "PART"));
        return;
    }
    // channel name from tokens[1] from the begning to the first ,
    std::string channel_name = tokens[1];
    Channel &channel = server.getChannelByName(channel_name);
    if (channel == *(server.getChannels().end()))
    {
        client.setSendBuffer(ERR_NOSUCHCHANNEL(server.getHostname(), client.getNickname(), channel_name));
        return;
    }
    // not in the channel
    if (!channel.clientExist(client))
    {
        client.setSendBuffer(ERR_NOTONCHANNEL(server.getHostname(), client.getNickname(), channel.getName()));
        return;
    }
    // see TARMAGX
    if (tokens[1].find(",") != std::string::npos)
        return;

    std::string reason = "";
    if (tokens.size() > 2)
    {
        if (tokens[2].find(":") == 0)
        {
            reason = message.substr(message.find(":")+1);
        }
        else
        {
            reason = tokens[2];
        }
    }
    channel.sendMessageToAll(RPL_PART(client.getHostname(), channel.getName(), client.getNickname(),client.getUsername(), reason));
    channel.removeClient(client);
    if (channel.getClients().size() == 0)
        server.removeChannel(channel);
}