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
            std::string line = *it;
            formatMessage(line);
            registerClient(line, client);
        }
        client.resetRecvBuffer();
    }
    return SUCCESS;
}