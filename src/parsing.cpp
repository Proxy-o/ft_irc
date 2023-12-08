#include "Server.hpp"
#include "commands.hpp"

static bool isValidData(Client &client)
{
    if (client.getNickname() == "" || client.getUsername() == "" || client.getRealname() == "")
        return false;
    return true;
}

int Server::parseMessage(int fd)
{
    Client &client = this->getClient(fd);
    std::string message = client.getRecvBuffer();
    if (message.find("\n") != std::string::npos)
    {
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
                    client.setIsWelcomed(true);
                }
            }
        }
        client.resetRecvBuffer();
    }
    return SUCCESS;
}