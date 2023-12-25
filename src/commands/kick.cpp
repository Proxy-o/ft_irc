#include "commands.hpp"

void kick(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> tokens = ft_split(message, " ");

    if (tokens.size() < 3)
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "KICK"));
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
    if (tokens[2].find(",") != std::string::npos)
        return;
    
    std::string nick_to_kick = tokens[2];
    Client &client_to_kick = server.getClientByNickname(nick_to_kick);
    if (client_to_kick == server.getClient(-1))
    {
        // TODO 
        return;
    }







}