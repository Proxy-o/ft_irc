#include "commands.hpp"

void ft_addOp(Server &server, Channel &channel, Client &client, std::string &nickname)
{
    Client *toOp = channel.getClientByNickname(nickname);
    if (toOp == NULL)
    {
        client.setSendBuffer(ERR_USERNOTINCHANNEL(server.getHostname(), client.getNickname(), nickname, channel.getName()));
    }
    else
    {
        channel.addop(*toOp);
        //look for message to send
    }
}

void ft_addKey(Channel &channel, std::string &key)
{
    if (key != "")
    {
        channel.setPassword(key);
        //look for message to send
    }
}

void ft_removeOp(Server &server, Channel &channel, Client &client, std::string &nickname)
{
    Client *toOp = channel.getClientByNickname(nickname);
    if (toOp == NULL)
    {
        client.setSendBuffer(ERR_USERNOTINCHANNEL(server.getHostname(), client.getNickname(), nickname, channel.getName()));
    }
    else
    {
        channel.removeOp(*toOp);
        //look for message to send
    }
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
    size_t token_index = 1;
    if (tokens.size() > 2)
    {
        mode = tokens[2];
        if (mode[0] == '+')
        {
            for (size_t i = 1; i < mode.size(); i++)
            {
                if (mode[i] == 'o')
                {
                    if (tokens.size() < 4 + token_index - 1)
                    {
                        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                        return;
                    }
                    ft_addOp(server, channel, client, tokens[3 + token_index - 1]);
                    token_index++;
                }
                else if (mode[i] == 'k')
                {
                    if (tokens.size() < 4 + token_index - 1)
                    {
                        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                        return;
                    }
                    ft_addKey(channel, tokens[3 + token_index - 1]);
                    token_index++;
                }
                else if (mode[i] == 'i')
                {
                    channel.setIsInviteOnly(true);
                    //look for message to send
                }
                else if (mode[i] == 'l')
                {
                    if (tokens.size() < 4 + token_index - 1)
                    {
                        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                        return;
                    }
                    if (tokens[3 + token_index - 1].find_first_not_of("0123456789") != std::string::npos)
                        return;
                    // FORBIDDEN FUNCTION STOI !!!!!
                    channel.setClientsLimit(std::atoi(tokens[3 + token_index - 1].c_str()));
                    token_index++;
                    //look for message to send
                }
                else if (mode[i] == 't')
                {
                    channel.setIsTopic(true);
                    //look for message to send
                }
            }
            return;
        }
        else if (mode[0] == '-')
        {
            for (size_t i = 1; i < mode.size(); i++)
            {
                if (mode[i] == 'o')
                {
                    if (tokens.size() < 4 + token_index - 1)
                    {
                        client.setSendBuffer(ERR_NEEDMOREPARAMS(server.getHostname(), client.getNickname(), "MODE"));
                        return;
                    }
                    ft_removeOp(server, channel, client, tokens[3 + token_index - 1]);
                    //look for message to send
                }
                else if (mode[i] == 'k')
                {
                    channel.setPassword("");
                    //look for message to send
                }
                else if (mode[i] == 'i')
                {
                    channel.setIsInviteOnly(false);
                    //look for message to send
                }
                else if (mode[i] == 'l')
                {
                    channel.setClientsLimit(0);
                    //look for message to send
                }
                else if (mode[i] == 't')
                {
                    channel.setIsTopic(false);
                    //look for message to send
                }
            }
        }
        else
        {
            client.setSendBuffer(ERR_UNKNOWNMODE(server.getHostname(), client.getNickname(), mode));
            return;
        }
    }
    
}