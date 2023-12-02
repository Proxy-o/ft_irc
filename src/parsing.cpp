#include "Server.hpp"

int Server::parseMessage(int fd)
{
    Client client = this->getClient(fd);
    std::string message = client.getBuffer();
    PRINT(BLUE << "Message received: " << message << RESET);
    return SUCCESS;
}