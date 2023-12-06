#include "Server.hpp"
#include "commands.hpp"

void Server::registerClient(Client &client, std::string message)
{
    std::vector<std::string> lines = ft_split(message, "\n");
    std::vector<std::string>::iterator it = lines.begin();
    for (; it != lines.end(); it++)
    {
        std::string line = *it;
        formatMessage(line);
        if (isCommand("NICK", line) == true)
            nick(line, client, *this);
        else if (isCommand("USER", line) == true)
            user(line, client);

    }
}