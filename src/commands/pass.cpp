#include "commands.hpp"

void pass(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> tokens = ft_split(message, " ");
    if (tokens.size() < 2)
    {
        client.setSendBuffer(ERR_NEEDMOREPARAMS(client.getNickname(), "PASS"));
        return;
    }
    if (tokens[1] == server.getPassword())
        client.setPassIsCorrect(true);
    else
    {
        client.setSendBuffer(ERR_PASSWDMISMATCH(client.getNickname()));
        client.setPassIsCorrect(false);
    }
    // TODO: handle ERR_ALREADYREGISTRED
}
