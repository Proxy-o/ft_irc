#include "Server.hpp"
#include "commands.hpp"

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
            std::cout << "line: " << *it << std::endl;
            std::string line = *it;
            formatMessage(line);
            if (client.isRegistered() == false)
                registerClient(line, client);
            else if (client.isRegistered())
            {
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
                else if (line.find("OPER") == 0)
                {
                    oper(line, client);
                }
                else if (line.find("PRIVMSG") == 0)
                {
                    privmsg(line, client, *this);
                }
            }
            client.resetRecvBuffer();
        }
    }
    return SUCCESS;
}
