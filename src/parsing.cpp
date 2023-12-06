#include "Server.hpp"

int Server::parseMessage(int fd)
{
    Client &client = this->getClient(fd);
    std::string message = client.getRecvBuffer();
    if (message.find("\r\n") != std::string::npos)
    {
        if (client.isRegistered() == false)
        {
            this->registerClient(client, message);
        }
        else
        {
            // handle commands
        }
        client.resetRecvBuffer();
    }
    return SUCCESS;
}