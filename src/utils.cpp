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
    tokens.push_back(buffer);
    return tokens;
}