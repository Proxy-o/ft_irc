#include <stdio.h>
#include <poll.h>
#include <iostream>
#include "Server.hpp"

int main(int argc, char **argv)
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: ./ircserv [port] [password]" << std::endl;
            return 1;
        }
        std::string port(argv[1]);
        std::string password(argv[2]);
        Server server(password, port);
        server.networkInit();
        server.runLoop();
    }
    catch (const std::exception &e)
    {
        std::cerr << RED << "Exception " << e.what() << RESET << std::endl;
    }
}
