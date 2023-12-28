#include "commands.hpp"

void topic(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> tokens = ft_split(message, " ");

    if (tokens.size() < 2)
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "TOPIC"));
        return;
    }
    Channel &channel = server.getChannelByName(tokens[1]);
    if (channel == *(server.getChannels().end()))
    {
        client.setSendBuffer(ERR_NOSUCHCHANNEL(server.getHostname(), client.getNickname(), tokens[1]));
        return;
    }
    // not in the channel
    if (!channel.clientExist(client))
    {
        client.setSendBuffer(ERR_NOTONCHANNEL(server.getHostname(), client.getNickname(), channel.getName()));
        return;
    }
    if (tokens.size() == 2)
    {
        if (channel.getTopic() == "")
        {
            client.setSendBuffer(RPL_NOTOPIC(server.getHostname(), client.getNickname(), channel.getName()));
            return;
        }
        client.setSendBuffer(RPL_TOPIC(server.getHostname(), client.getNickname(), channel.getName(), channel.getTopic()));
        client.setSendBuffer(RPL_TOPICWHOTIME(server.getHostname(), client.getNickname(), channel.getName(), channel.getTopicSetter(), channel.getTopicDate()));
        return;
    }
    std::string msg;
    if (tokens.size() >= 3)
    {
        if (tokens[2].find(":") == 0)
        {
            msg = message.substr(message.find(":") + 1);
        }
        else
        {
            msg = tokens[2];
        }
        channel.setTopic(msg);
        channel.setTopicSetter(client);
        channel.setTopicDate();
        channel.sendMessageToAll(RPL_TOPIC(server.getHostname(), client.getNickname(), channel.getName(), channel.getTopic()));
    }
}
