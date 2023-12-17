#include "utils.hpp"
#include <vector>

#include <vector>
#include <string>

std::vector<std::string> ft_split(std::string buffer, std::string delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;

    // Handle leading delimiters
    while (buffer.substr(0, delimiter.length()) == delimiter)
    {
        buffer.erase(0, delimiter.length());
    }

    while ((pos = buffer.find(delimiter)) != std::string::npos)
    {
        token = buffer.substr(0, pos);
        tokens.push_back(token);

        // Skip consecutive delimiters (if any) and handling the case where the delimiter is at the end of the string
        buffer.erase(0, pos + delimiter.length());
        while (buffer.substr(0, delimiter.length()) == delimiter)
        {
            buffer.erase(0, delimiter.length());
        }
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

bool isCommand(std::string cmd, std::string message)
{
    std::vector<std::string> tokens = ft_split(message, " ");
    if (tokens.size() == 0)
        return false;
    if (tokens[0] == cmd)
        return true;
    return false;
}
