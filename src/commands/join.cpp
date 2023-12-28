#include "Channel.hpp"

void sendNames(Channel &channel, Client &client, Server &server)
{
    std::string rpl = RPL_NAMREPLY(server.getHostname(), client.getNickname(), channel.getName());
    std::map<int, Client *>::iterator clients = channel.getClients().begin();
    for (; clients != channel.getClients().end(); clients++)
    {
        rpl += channel.isOp(*clients->second);
        rpl += clients->second->getNickname() + " ";
    }
    rpl += "\r\n";
    client.setSendBuffer(rpl);
}

void join(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> keys;
    std::vector<std::string> params = ft_split(message, " ");
    size_t channel_index = 0;
    // PRINT("JOIN");
    if (params.size() < 2)
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "JOIN"));
        return;
    }
    std::vector<std::string> channels = ft_split(params[1], ",");
    if (params.size() == 3)
        keys = ft_split(params[2], ",");
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i].find_first_of(" ,\a\n\t\r\v\b\f\r\n") != std::string::npos)
            continue;
        if (channels[i][0] != '#') // &
        {
            continue;
        }
        std::vector<Channel>::iterator it = server.getChannels().begin();
        bool channel_exist = false;
        for (; it != server.getChannels().end(); it++)
        {
            if (it->getName() == channels[i])
            {
                channel_exist = true;
                break;
            }
        }
        if (!channel_exist)
        {
            Channel new_channel(&client, client.getClientSockfd());
            new_channel.setName(channels[i]);
            server.getChannels().push_back(new_channel);
            it = server.getChannels().end() - 1;
        }
        else
        {
            if (it->clientExist(client))
            {
                it->setReplay(102, server, client);
                continue;
            }
            if (it->getModes().find("k") != std::string::npos)
            {
                if ((keys.size() > channel_index && keys[channel_index] != it->getPassword()) || keys.size() <= channel_index)
                {
                    client.setSendBuffer(ERR_BADCHANNELKEY(server.getHostname(), client.getNickname(), it->getName()));
                    continue;
                }
            }
            it->addClient(client);
        }
        std::string realname = (client.getRealname().find_last_of(" ") != std::string::npos) ? ":" + client.getRealname() : client.getRealname();
        it->sendMessageToAll(RPL_JOIN(client.getNickname(), it->isOp(client), client.getUsername(), client.getHostname(), it->getName()));
        it->sendMessageToAll(":" + server.getHostname() + " " + client.getNickname() + " JOIN " + it->getName() + "\r\n");
        if (it->getTopic() != "")
        {
            it->setReplay(332, server, client);
            it->setReplay(333, server, client);
        }
        sendNames(*it, client, server);
        it->setReplay(366, server, client);
        // it->sendMessageToAllExcept(":" + server.getHostname() + " " + client.getNickname() + " JOIN " + it->getName() + "\r\n", client);
        channel_index++;
    }
}
