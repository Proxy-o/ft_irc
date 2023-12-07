#include "commands.hpp"

void pass(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> tokens = ft_split(message, " ");
    client.setNickname("");
    client.setUsername("");
    client.setRealname("");
    if (tokens.size() < 2)
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(client.getNickname(), "PASS"));
        return;
    }
    if (tokens[1] == server.getPassword())
        client.setIsPassCorrect(true);
    else
    {
        client.setSendBuffer(ERR_PASSWDMISMATCH(client.getNickname()));
        client.setIsPassCorrect(false);
    }

    // TODO: handle ERR_ALREADYREGISTRED
}
