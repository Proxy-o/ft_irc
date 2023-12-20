#include "Server.hpp"
#include "commands.hpp"

static bool isValidData(Client &client)
{
    if (client.getNickname() == "" || client.getUsername() == "" || client.getRealname() == "")
        return false;
    return true;
}

int Server::registerClient(std::string line, Client &client)
{
    if (line.find("NICK") == 0)
    {
        nick(line, client, *this);
    }
    else if (line.find("USER") == 0)
    {
        user(line, client, *this);
    }
    else if (line.find("PASS") == 0 && client.isRegistered() == false)
    {
        pass(line, client, *this);
    }
    else if (line.find("PASS") == 0 && client.isRegistered() == true)
    {
        client.setReplay(462, *this);
    }
    if (isValidData(client) == true && client.isPassCorrect() == true)
    {
        client.setIsRegistered(true);
        if (client.isWelcomed() == false)
        {
            client.setReplay(001, *this);
            client.setReplay(002, *this);
            client.setReplay(003, *this);
            client.setReplay(004, *this);
            client.setReplay(005, *this);
            client.setIsWelcomed(true);
        }
    }
    return SUCCESS;
}