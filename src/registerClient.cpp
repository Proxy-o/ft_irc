#include "Server.hpp"
#include "commands.hpp"

static bool isValidData(Client &client)
{
    if (client.getNickname() == "" || client.getUsername() == "" || client.getRealname() == "")
        return false;
    return true;
}

int Server::registerClient(Client &client, std::string message)
{
    // TODO: handle multiple lines YOU ARE IN  A LOOP MTFK
    std::vector<std::string> lines = ft_split(message, "\n");
    std::vector<std::string>::iterator it = lines.begin();
    for (; it != lines.end(); it++)
    {
        std::string line = *it;
        formatMessage(line);
        if (line.find("NICK") == 0)
        {
            nick(line, client, *this);
        }
        else if (line.find("USER") == 0)
        {
            user(line, client);
        }
        else if (line.find("PASS") == 0)
        {
            pass(line, client, *this);
        }
        if (isValidData(client) == true && client.isPassCorrect() == true)
        {
            client.setReplay(001);
            client.setIsRegistered(true);
        }
    }
    return SUCCESS;
}