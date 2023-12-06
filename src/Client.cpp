#include "Client.hpp"

Client::Client(int sockfd) 
{
    this->_client_sockfd = sockfd;
    this->_recv_buffer = "";
}

Client::~Client()
{
}

Client &Client::operator=(const Client &client)
{
    this->_client_sockfd = client._client_sockfd;
    this->_recv_buffer = client._recv_buffer;
    this->_send_buffer = client._send_buffer;
    this->_is_registered = client._is_registered;
    this->_nickname = client._nickname;
    return *this;
}

bool Client::operator==(const Client &client) const
{
    // compare the addresses of the two objects and return true if they are equal
    return this == &client;
}

bool Client::operator!=(const Client &client) const
{
    // compare the two objects and return true if they are not equal
    return !(*this == client); 
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

void Client::setSendBuffer(std::string buffer)
{
    this->_send_buffer += buffer;
}

std::string Client::getSendBuffer()
{
    return this->_send_buffer;
}
void Client::resetSendBuffer()
{
    this->_send_buffer = "";
}

void Client::setNickname(std::string nickname)
{
    this->_nickname = nickname;
}

std::string Client::getNickname()
{
    return this->_nickname;
}