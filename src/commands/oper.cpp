#include "commands.hpp"
#include "utils.hpp"

void oper(std::string &message, Client &client)
{
    std::vector<std::string> params = ft_split(message, " ");
    if (params.size() != 3)
    {
        client.setReplay(461);
        return;
    }
    if (params[1] == OPER_NAME && params[2] == OPER_PASS)
    {
        client.setIsOperator(true);
        client.setReplay(381);
    }
    else
    {
        client.setReplay(464);
    }
}