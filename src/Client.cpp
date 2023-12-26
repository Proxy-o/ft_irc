#include "Client.hpp"

Client::Client()
{
}

Client::Client(int sockfd)
{
    this->_client_sockfd = sockfd;
    this->_recv_buffer = "";
    this->_send_buffer = "";
    this->_is_registered = false;
    this->_is_welcomed = false;
    this->_nickname = "*";
    this->_hostname = getClientHostname();
    this->_need_to_quit = false;
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

void Client::setHostname(std::string hostname)
{
    this->_hostname = hostname;
}

std::string Client::getRealname()
{
    return this->_realname;
}

void Client::setIsPassCorrect(bool status)
{
    this->_pass_is_correct = status;
}

bool Client::isPassCorrect()
{
    return this->_pass_is_correct;
}

void Client::setIsWelcomed(bool status)
{
    this->_is_welcomed = status;
}

bool Client::isWelcomed()
{
    return this->_is_welcomed;
}

void Client::setIsOperator(bool status)
{
    this->is_operator = status;
}

bool Client::isOperator()
{
    return this->is_operator;
}

int Client::getClientSockfd()
{
    return this->_client_sockfd;
}

std::string Client::getClientHostname()
{
    char hostname[NI_MAXHOST];
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);

    getpeername(this->_client_sockfd, (struct sockaddr *)&addr, &len);
    int result = getnameinfo((struct sockaddr *)&addr, sizeof(struct sockaddr_storage),
                             hostname, NI_MAXHOST, nullptr, 0, 0);
    if (result != 0)
    {
        return gai_strerror(result);
    }
    std::string hostname_str = std::string(hostname);
    if (hostname_str == "localhost" || hostname_str == "127.0.0.1")
    {
        if (gethostname(hostname, sizeof(hostname)) == -1)
        {
            throw std::runtime_error("gethostname Error: can't get hostname");
        }
        hostname_str = std::string(hostname);
    }
PRINT("hostname_str: " << hostname_str)
    return hostname_str;
}

std::string Client::getHostname()
{
    return this->_hostname;
}

void Client::setNeedToQuit(bool status)
{
    this->_need_to_quit = status;
}

bool Client::needToQuit()
{
    return this->_need_to_quit;
}