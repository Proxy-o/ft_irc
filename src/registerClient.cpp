#include "Server.hpp"

void Server::registerClient(Client &client, std::string message)
{

    (void)client;
    std::vector<std::string> lines = ft_split(message, "\n");
    std::vector<std::string>::iterator it = lines.begin();
    for (; it != lines.end(); it++)
    {
        std::string line = *it;
        std::vector<std::string> tokens = ft_split(line, " ");
        if (tokens[0] == "NICK")
            PRINT("HANDLE NICK")
        else if (tokens[0] == "USER")
            PRINT("HANDLE USER")
        else if (tokens[0] == "PASS")
            PRINT("HANDLE PASS")
    
    }
}