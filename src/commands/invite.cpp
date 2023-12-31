#include "commands.hpp"
#include "Client.hpp"

void invite(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> tokens = ft_split(message, " ");
    if (tokens.size() == 1)
    {
        std::string channelList = "";
        std::vector<Channel>::iterator it = server.getChannels().begin();
        for (; it != server.getChannels().end(); it++)
        {
            if (it->clientIsInvited(client))
            {
                channelList += client.getNickname() + " " + it->getName() + "\r\n";
            }
        }
        client.setSendBuffer(channelList);
        client.setSendBuffer(RPL_ENDOFINVITELIST(server.getHostname(), client.getNickname()));
        return;
    }
    if (tokens.size() < 3)
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "INVITE"));
        return;
    }
    std::map<int, Client>::iterator it = server.getClients().begin();
    Client *toInvite = NULL;
    for (; it != server.getClients().end(); it++)
    {
        if (it->second.getNickname() == tokens[1])
        {
            toInvite = &it->second;
            break;
        }
    }
    if (toInvite == NULL)
    {
        client.setSendBuffer(ERR_NOSUCHNICK(server.getHostname(), client.getNickname(), tokens[1]));
        return;
    }
    Channel &channel = server.getChannelByName(tokens[2]);
    if (channel == *(server.getChannels().end()))
    {
        client.setSendBuffer(ERR_NOSUCHCHANNEL(server.getHostname(), client.getNickname(), tokens[2]));
        return;
    }
    if (!channel.clientExist(client))
    {
        client.setSendBuffer(ERR_NOTONCHANNEL(server.getHostname(), client.getNickname(), channel.getName()));
        return;
    }
    if (channel.clientExist(*toInvite))
    {
        client.setSendBuffer(ERR_USERONCHANNEL(server.getHostname(), client.getNickname(), toInvite->getNickname(), channel.getName()));
        return;
    }
    channel.getInvitedClients().insert(std::pair<int, Client *>(toInvite->getClientSockfd(), toInvite));
    client.setSendBuffer(RPL_INVITING(server.getHostname(), client.getNickname(), toInvite->getNickname(), channel.getName()));
    client.setSendBuffer(":" + client.getNickname() + " INVITE " + toInvite->getNickname() + " " + channel.getName() + "\r\n");
    toInvite->setSendBuffer(":" + client.getNickname() + " INVITE " + toInvite->getNickname() + " " + channel.getName() + "\r\n");
}