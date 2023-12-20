#include "commands.hpp"

void pass(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> tokens = ft_split(message, " ");
    client.setNickname("");
    client.setUsername("");
    client.setRealname("");
    if (tokens.size() < 2)
    {
        client.setReplay(461, server);
        return;
    }
    if (tokens[1] == server.getPassword())
        client.setIsPassCorrect(true);
    else
    {
        client.setReplay(464, server);
        client.setIsPassCorrect(false);
    }

    // TODO: handle ERR_ALREADYREGISTRED
}
