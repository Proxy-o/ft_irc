#include "Server.hpp"
#include "commands.hpp"

void Server::registerClient(Client &client, std::string message)
{
    std::vector<std::string> lines = ft_split(message, "\n");
    std::vector<std::string>::iterator it = lines.begin();
    for (; it != lines.end(); it++)
    {
        std::string line = *it;
        formatMessage(line);
        std::vector<std::string> tokens = ft_split(line, " ");
        
        // Remove \n\r from the start and the end of the string if it exists
        
        if (tokens[0] == "NICK")
            nick(tokens, client, *this);
        // else if (tokens[0] == "USER")
        //     PRINT("HANDLE USER")
        // else if (tokens[0] == "PASS")
        //     PRINT("HANDLE PASS")
    
    }
}