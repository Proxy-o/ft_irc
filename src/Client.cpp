#include "Client.hpp"

Client::Client(int sockfd)
{
    this->_client_sockfd = sockfd;
    this->_recv_buffer = "";
    this->_send_buffer = "";
    this->_is_registered = false;
    this->_nickname = "";
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

void Client::setUsername(std::string username)
{
    this->_username = username;
}

std::string Client::getUsername()
{
    return this->_username;
}

void Client::setRealname(std::string realname)
{
    this->_realname = realname;
}

std::string Client::getRealname()
{
    return this->_realname;
}

void Client::setPassIsCorrect(bool status)
{
    this->_pass_is_correct = status;
}

bool Client::passIsCorrect()
{
    return this->_pass_is_correct;
}