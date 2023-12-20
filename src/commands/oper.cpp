#include "commands.hpp"
#include "utils.hpp"

void oper(std::string &message, Client &client, Server &server)
{
    std::vector<std::string> params = ft_split(message, " ");
    if (params.size() != 3)
    {
        client.setReplay(461, server);
        return;
    }
    if (params[1] == OPER_NAME && params[2] == OPER_PASS)
    {
        client.setIsOperator(true);
        client.setReplay(381, server);
    }
    else
    {
        client.setReplay(464, server);
    }
}