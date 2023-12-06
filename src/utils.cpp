#include "utils.hpp"
#include <vector>

std::vector<std::string> ft_split(std::string buffer, std::string delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = buffer.find(delimiter)) != std::string::npos )
    {
        token = buffer.substr(0, pos);
        tokens.push_back(token);
        buffer.erase(0, pos + delimiter.length());
    }
    if (buffer != "")
    tokens.push_back(buffer);
    return tokens;
}

void printVector(std::vector<std::string> &vec)
{
    std::vector<std::string>::iterator it = vec.begin();
    for (; it != vec.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}

void formatMessage(std::string &message)
{
    size_t start = message.find_first_not_of(" \n\r\"");
    size_t end = message.find_last_not_of(" \n\r\"");
    if (start != std::string::npos && end != std::string::npos)
    {
        message = message.substr(start, end - start + 1);
    }
}