#include "Server.hpp"
#include "commands.hpp"

static bool isValidCommand(std::string line)
{
    if (line.find("NICK") == 0 || line.find("USER") == 0 || line.find("PASS") == 0 || line.find("OPER") == 0 
    || line.find("PRIVMSG") == 0 || line.find("JOIN") == 0 || line.find("PING") == 0 || line.find("PONG") == 0 
    || line.find("TOPIC") == 0 || line.find("KICK") == 0 || line.find("MODE") == 0)
        return true;
    return false;
}

int Server::parseMessage(int fd)
{
    Client &client = this->getClient(fd);
    std::string message = client.getRecvBuffer();
    // PRINT("message: " + message);
    if (message.find("\n") != std::string::npos)
    {

        std::vector<std::string> lines = ft_split(message, "\n");
        std::vector<std::string>::iterator it = lines.begin();
        for (; it != lines.end(); it++)
        {
            std::string line = *it;
            formatMessage(line);
            if (client.isRegistered() == false && isValidCommand(line) == true)
                registerClient(line, client);
            else if (client.isRegistered() && isValidCommand(line) == true)
            {
                if (line.find("NICK") == 0)
                {
                    nick(line, client, *this);
                }
                else if (line.find("USER") == 0)
                {
                    user(line, client, *this);
                }
                else if (line.find("PASS") == 0)
                {
                    pass(line, client, *this);
                }
                else if (line.find("OPER") == 0)
                {
                    oper(line, client, *this);
                }
                else if (line.find("PRIVMSG") == 0)
                {
                    privmsg(line, client, *this);
                }
                else if (line.find("JOIN") == 0)
                {
                    join(line, client, *this);
                }
                else if (line.find("PONG") == 0 || line.find("PING") == 0)
                {
                    ping_pong(line, client);
                }
                else if (line.find("TOPIC") == 0)
                {
                    topic(line, client, *this);
                }
                else if (line.find("KICK") == 0)
                {
                    kick(line, client, *this);
                }
             }
                else
                {
                    client.setSendBuffer("INVALID COMMAND: " + line +"\r\n");
                }
            client.resetRecvBuffer();
        }
    }
    return SUCCESS;
}
