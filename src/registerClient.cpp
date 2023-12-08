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
        user(line, client);
    }
    else if (line.find("PASS") == 0 && client.isRegistered() == false)
    {
        pass(line, client, *this);
    }
    else if (line.find("PASS") == 0 && client.isRegistered() == true)
    {
        client.setReplay(462);
    }
    if (isValidData(client) == true && client.isPassCorrect() == true)
    {
        client.setIsRegistered(true);
        if (client.isWelcomed() == false)
        {
            client.setReplay(001);
            client.setReplay(002);
            client.setReplay(003);
            client.setReplay(004);
            client.setReplay(005);
            client.setIsWelcomed(true);
        }
    }
    return SUCCESS;
}