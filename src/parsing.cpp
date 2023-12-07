#include "Server.hpp"

int Server::parseMessage(int fd)
{
    Client &client = this->getClient(fd);
    std::string message = client.getRecvBuffer();
    if (message.find("\r\n") != std::string::npos)
    {
        if (client.isRegistered() == false)
        {
            if (this->registerClient(client, message) == SUCCESS)
            {
                // client.setSendBuffer(RPL_WELCOME(client.getNickname()));
            }
        }
        else
        {
            // handle commands
        }
        client.resetRecvBuffer();
    }
    return SUCCESS;
}