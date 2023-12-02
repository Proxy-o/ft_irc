#include "Client.hpp"

Client::Client(int sockfd) 
{
    this->_client_sockfd = sockfd;
}

Client::~Client()
{
}



void Client::setBuffer(std::string buffer)
{
    this->_buffer = buffer;
}

std::string Client::getBuffer()
{
    return this->_buffer;
}