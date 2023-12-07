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
        if (isCommand("PASS", line) == true && client.isRegistered() == false)
        {
            pass(line, client, *this);
            return SUCCESS;
        }
        else if (isCommand("PASS", line) == true && client.isRegistered() == true)
        {
            client.setSendBuffer(ERR_ALREADYREGISTERED(client.getNickname()));
            return SUCCESS;
        }
        else if (isCommand("NICK", line) == true)
        {
            nick(line, client, *this);
            return SUCCESS;
        }
        else if (isCommand("USER", line) == true)
        {
            user(line, client);
            return SUCCESS;
        }
        if (isValidData(client) == true && client.isPassCorrect() == true)
            return SUCCESS;
        else
        {
            client.setSendBuffer(ERR_NOTREGISTERED(client.getNickname()));
            return FAIL;
        }
    }
    return FAIL;
}