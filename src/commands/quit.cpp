#include "commands.hpp"

void quit(std::string &message, Client &client)
{
    std::vector<std::string> tokens = ft_split(message, " ");

    std::string reason = "";
    if (tokens.size() > 1)
    {
        if (tokens[1].find(":") == 0)
        {
            reason = message.substr(message.find(":")+1);
        }
        else
        {
            reason = tokens[1];
        }
    }
    client.setSendBuffer(":" + client.getNickname() + " QUIT :" + reason + "\r\n");
    client.setNeedToQuit(true);
}