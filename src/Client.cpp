#include "Client.hpp"

Client::Client(int sockfd) 
{
    this->_client_sockfd = sockfd;
}

Client::~Client()
{
}
