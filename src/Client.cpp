#include "Client.hpp"

Client::Client(int sockfd) 
{
    this->_client_sockfd = sockfd;
    this->_recv_buffer = "";
}

Client::~Client()
{
}

void Client::resetRecvBuffer()
{
    this->_recv_buffer = "";
}


void Client::setRecvBuffer(std::string buffer)
{
    this->_recv_buffer += buffer;
}

std::string Client::getRecvBuffer()
{
    return this->_recv_buffer;
}

void Client::setIsRegistered(bool status)
{
    this->_is_registered = status;
}

bool Client::isRegistered()
{
    return this->_is_registered;
}
