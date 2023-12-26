#include "commands.hpp"

void mode(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> tokens = ft_split(message, " ");
    if (tokens.size() < 2)
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
        return;
    }
    std::string targetName = tokens[1];
    Channel &channel = server.getChannelByName(targetName);
    if (channel == server.getChannel(""))
    {
        client.setSendBuffer(ERR_NOSUCHCHANNEL(server.getHostname(), client.getNickname(), targetName));
        return;
    }
    if (channel != server.getChannel(""))
    {
        if (tokens.size() == 2)
        {
            client.setSendBuffer(RPL_CHANNELMODEIS(server.getHostname(), client.getNickname(), channel.getName(), channel.getModes()));
            return;
        }
    }
    else
    {
        client.setSendBuffer(ERR_NOSUCHCHANNEL(server.getHostname(), client.getNickname(), channel.getName()));
        return;
    }
    std::string mode;
    if (tokens.size() > 2)
    {
        if (tokens[2] == "+k")
        {
            if (tokens.size() < 4)
            {
                client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                return;
            }
            std::string password = tokens[3];
            channel.setPassword(password);
            if (channel.getModes().find("k") == std::string::npos)
                channel.setModes(channel.getModes() + "k " + password);
            else
            {
                mode = channel.getModes();
                mode = mode.substr(0, mode.find(" ") + 1) + password;
            }
            return;
        }
        else if (tokens[2] == "-k")
        {
            if (tokens.size() < 4)
            {
                client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                return;
            }
            std::string password = tokens[3];
            if (channel.getPassword() != password)
            {
                client.setSendBuffer(ERR_BADCHANNELKEY(server.getHostname(), client.getNickname(), channel.getName()));
                return;
            }
            channel.setPassword("");
            if (channel.getModes().find("k") != std::string::npos)
            {
                mode = channel.getModes();
                mode = mode.substr(0, mode.find(" "));
            }
            return;
        }
        else if (tokens[2] == "+o")
        {
            if (tokens.size() < 4)
            {
                client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                return;
            }
            std::string nickname = tokens[3];
            Client &target = server.getClientByNickname(nickname);
            if (target == server.getClient(-1))
            {
                client.setSendBuffer(ERR_NOSUCHNICK(server.getHostname(), client.getNickname(), nickname));
                return;
            }
            if (!channel.clientExist(target))
            {
                client.setSendBuffer(ERR_USERNOTINCHANNEL(server.getHostname(), client.getNickname(), nickname, channel.getName()));
                return;
            }
            if (channel.isOp(client) == "@")
            {
                client.setSendBuffer(ERR_CHANOPRIVSNEEDED(server.getHostname(), client.getNickname(), channel.getName()));
                return;
            }
            // check if already op
            channel.addop(target);
            return;
        }
        else if (tokens[2] == "-o")
        {
            if (tokens.size() < 4)
            {
                client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                return;
            }
            std::string nickname = tokens[3];
            Client &target = server.getClientByNickname(nickname);
            if (target == server.getClient(-1))
            {
                client.setSendBuffer(ERR_NOSUCHNICK(server.getHostname(), client.getNickname(), nickname));
                return;
            }
            if (!channel.clientExist(target))
            {
                client.setSendBuffer(ERR_USERNOTINCHANNEL(server.getHostname(), client.getNickname(), nickname, channel.getName()));
                return;
            }
            if (channel.isOp(client) == "@")
            {
                client.setSendBuffer(ERR_CHANOPRIVSNEEDED(server.getHostname(), client.getNickname(), channel.getName()));
                return;
            }
            // check if already op
            channel.removeOp(target);
        }
        else{
            client.setSendBuffer(ERR_UNKNOWNMODE(server.getHostname(), client.getNickname(), tokens[2]));
            return;
        }
    }
    
}