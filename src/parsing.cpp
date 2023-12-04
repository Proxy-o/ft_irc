#include "Server.hpp"

int Server::parseMessage(int fd)
{
    Client &client = this->getClient(fd);
    std::string message = client.getRecvBuffer();
    if (message.find("\r\n") != std::string::npos)
       {
        if (client.isRegistered() == false)
        {
            std::vector<std::string> lines = splitBuffer(message, "\n");
            std::vector<std::string>::iterator it = lines.begin();
            for (; it != lines.end(); it++)
            {
                PRINT(*it);
            }
            
        }
        else
        {
            // handle commands
        }
       }
    return SUCCESS;
}