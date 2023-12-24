#include "commands.hpp"

void ping_pong(std::string &message, Client &client)
{
    std::string token = message.substr(5);
    std::string prefix;
    if (message.find("PING") == 0)
    {
        prefix = "PONG";
    }
    else if (message.find("PONG") == 0)
    {
        prefix = "PING";
    }
    std::string rpl = prefix + " " + token + "\r\n";
    client.setSendBuffer(rpl);
}