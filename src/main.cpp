#include <stdio.h>
#include <poll.h>
#include <iostream>
#include "Server.hpp"

int main(void)
{
    try
    {
        Server server("1234", "8080");
        server.networkInit();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception " << e.what() << std::endl;
    }
}
