#include "commands.hpp"

void user(std::string &message, Client &client)
{

    std::vector<std::string> tokens = ft_split(message, " ");
    std::string realName;
    bool semicolon = false;

    if (tokens.size() < 5)
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(client.getNickname(), "USER"));
        return;
    }
    if (tokens[2] != "0" || tokens[3] != "*")
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(client.getNickname(), "USER"));
        return;
    }
    if (tokens.size() > 5 && tokens[4].find_first_of(":") == 0)
    {
        tokens[4].erase(0, 1);
        semicolon = true;
    }
    if (semicolon == true)
    {
        for (size_t i = 4; i < tokens.size(); i++)
        {
            realName += tokens[i];
            if (i != tokens.size() - 1)
                realName += " ";
        }
    }
    else
        realName = tokens[4];
    client.setUsername(tokens[1]);
    client.setRealname(realName);
    // TODO : send already registered message
}
