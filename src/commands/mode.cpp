#include "commands.hpp"

int ft_addOp(Server &server, Channel &channel, Client &client, std::string &nickname)
{
    Client *toOp = channel.getClientByNickname(nickname);
    if (toOp == NULL)
    {
        client.setSendBuffer(ERR_USERNOTINCHANNEL(server.getHostname(), client.getNickname(), nickname, channel.getName()));
        return (0);
    }
    channel.addop(*toOp);
    return (1);
}

int ft_addKey(Channel &channel, std::string &key)
{
    if (key != "")
    {
        channel.setPassword(key);
        return 1;
    }
    return 0;
}

int ft_removeOp(Server &server, Channel &channel, Client &client, std::string &nickname)
{
    Client *toOp = channel.getClientByNickname(nickname);
    if (toOp == NULL)
    {
        client.setSendBuffer(ERR_USERNOTINCHANNEL(server.getHostname(), client.getNickname(), nickname, channel.getName()));
        return (0);
    }
    channel.removeOp(*toOp);
    return (1);
}

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
    if (channel.clientExist(client) == false)
    {
        client.setSendBuffer(ERR_NOTONCHANNEL(server.getHostname(), client.getNickname(), channel.getName()));
        return;
    }
    if (tokens.size() == 2)
    {
        client.setSendBuffer(RPL_CHANNELMODEIS(server.getHostname(), client.getNickname(), channel.getName(), channel.getModes()));
        return;
    }
    if (channel.isOp(client) != "@" && client.isOperator() == false)
    {
        client.setSendBuffer(ERR_CHANOPRIVSNEEDED(server.getHostname(), client.getNickname(), channel.getName()));
        return;
    }
    std::string mode;
    std::string applied_modes = "";
    std::string applied_modes_args = "";
    size_t token_index = 1;
    if (tokens.size() > 2)
    {
        mode = tokens[2];
        if (mode[0] == '+')
        {
            for (size_t i = 1; i < mode.size(); i++)
            {
                size_t param_index = 3 + token_index - 1;
                token_index++;
                if (mode[i] == 'o')
                {
                    if (tokens.size() < param_index + 1)
                    {
                        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                        return;
                    }
                    if (ft_addOp(server, channel, client, tokens[param_index]) == 0)
                        continue;
                    applied_modes += "o";
                    applied_modes_args += " " + tokens[param_index];
                }
                else if (mode[i] == 'k')
                {
                    if (tokens.size() < param_index + 1)
                    {
                        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                        return;
                    }
                    if (ft_addKey(channel, tokens[param_index]) == 0)
                        continue;
                    applied_modes += "k";
                    applied_modes_args += " " + tokens[param_index];
                }
                else if (mode[i] == 'i')
                {
                    channel.setIsInviteOnly(true);
                    applied_modes += "i";
                }
                else if (mode[i] == 'l')
                {
                    if (tokens.size() < param_index + 1)
                    {
                        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                        return;
                    }
                    if (tokens[param_index].find_first_not_of("0123456789") != std::string::npos)
                        continue;
                    channel.setClientsLimit(std::atoi(tokens[param_index].c_str()));
                    applied_modes += "l";
                    applied_modes_args += " " + tokens[param_index];
                }
                else if (mode[i] == 't')
                {
                    channel.setIsTopic(true);
                    applied_modes += "t";
                }
            }
            mode = "+" + applied_modes + applied_modes_args;
            client.setSendBuffer(RPL_MODE(server.getHostname(), channel.getName(), mode));
            return;
        }
        else if (mode[0] == '-')
        {
            for (size_t i = 1; i < mode.size(); i++)
            {
                size_t param_index = 3 + token_index - 1;
                if (mode[i] == 'o')
                {
                    if (tokens.size() < param_index + 1)
                    {
                        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                        return;
                    }
                    if (ft_removeOp(server, channel, client, tokens[param_index]) == 0)
                        continue;
                    applied_modes += "o";
                    applied_modes_args += " " + tokens[param_index];
                }
                else if (mode[i] == 'k')
                {
                    channel.setPassword("");
                    applied_modes += "k";
                }
                else if (mode[i] == 'i')
                {
                    channel.setIsInviteOnly(false);
                    applied_modes += "i";
                }
                else if (mode[i] == 'l')
                {
                    channel.setClientsLimit(0);
                    applied_modes += "l";
                }
                else if (mode[i] == 't')
                {
                    channel.setIsTopic(false);
                    applied_modes += "t";
                }
            }
            mode = "-" + applied_modes + applied_modes_args;
            client.setSendBuffer(RPL_MODE(server.getHostname(), channel.getName(), mode));
        }
        else
        {
            client.setSendBuffer(ERR_UNKNOWNMODE(server.getHostname(), client.getNickname(), mode));
            return;
        }
    }
    
}