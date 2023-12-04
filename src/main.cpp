#include <stdio.h>
#include <poll.h>
#include <iostream>
#include "Server.hpp"

int main(void)
{
    try
    {
        Server server("1234", "6667");
        server.networkInit();
        server.runLoop();
    }
    catch (const std::exception &e)
    {
        std::cerr << RED << "Exception " << e.what() << RESET << std::endl;
    }
}
