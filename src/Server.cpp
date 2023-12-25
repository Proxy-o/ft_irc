#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

Server::Server()
{
}

Server::Server(std::string password, std::string port) : _password(password), _port(port)
{

    this->setCreationDate();
}

Server::~Server()
{
}

void Server::removeClient(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator it)
{
    std::vector<Channel>::iterator it2 = this->_channels.begin();
    for (; it2 != this->_channels.end(); it2++)
    {
        if (it2->clientExist(this->getClient(it->fd)))
        {
            it2->removeClient(this->getClient(it->fd));
        }
    }
    this->_clients.erase(it->fd);
    close(it->fd);
    poll_fds.erase(it);
    PRINT(RED << "Client disconnected" << RESET);
}

int Server::recvMessage(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator it)
{
    char buffer[513];
    bzero(buffer, sizeof(buffer));
    int recv_status = recv(it->fd, buffer, sizeof(buffer) - 1, 0);
    if (recv_status <= 0)
    {
        if (recv_status == -1)
            PRINT_ERR(RED << "recv Error" << RESET);
        removeClient(poll_fds, it);
        return FAIL;
    }
    std::string message(buffer);
    Client &client = this->getClient(it->fd);
    if (message.find("\n") == std::string::npos && (client.getRecvBuffer().length() >= 512 || message.length() >= 512))
    {
        client.resetRecvBuffer();
        return FAIL;
    }
    client.setRecvBuffer(message);
    if (message.find("PING") != 0 && message.find("PONG") != 0)
        PRINT(YELLOW << "<= CLIENT  " << client.getNickname() << " : " << client.getRecvBuffer() << RESET);
    return SUCCESS;
}

int Server::runLoop()
{
    std::vector<pollfd> poll_fds;
    add_pollfd(poll_fds, POLLIN, this->_serv_sockfd);

    while (true)
    {
        std::vector<int> fds_to_add;
        int poll_status = poll(&poll_fds[0], poll_fds.size(), -1);
        if (poll_status == -1)
        {
            throw std::runtime_error("poll Error");
        }
        for (std::vector<pollfd>::iterator it = poll_fds.begin(); it != poll_fds.end(); it++)
        {
            if (it->revents & POLLIN)
            {
                if (it->fd == this->_serv_sockfd)
                {
                    int client_sockfd = acceptNewConnection();
                    if (client_sockfd == FAIL)
                        continue;
                    fds_to_add.push_back(client_sockfd);
                    PRINT(GREEN << "New connection" << RESET);
                }
                else
                {
                    int recv_status = recvMessage(poll_fds, it);
                    if (recv_status == FAIL)
                        break;
                    else if (recv_status == SUCCESS)
                    {
                        parseMessage(it->fd);
                    }
                }
            }
            else if (it->revents & POLLOUT)
            {
                Client &client = this->getClient(it->fd);
                std::string message = client.getSendBuffer();
                if (message != "")
                {
                    // DO NOT PRINT PING PONG
                    if (message.find("PING") != 0 && message.find("PONG") != 0)
                        PRINT(BLUE << "=> SERVER  : " << message << RESET);
                    int send_status = send(it->fd, message.c_str(), message.length(), 0);
                    if (send_status == -1)
                    {
                        PRINT_ERR(RED << "send Error" << RESET);
                        return FAIL;
                    }
                    else
                    {
                        client.resetSendBuffer();
                        client.resetRecvBuffer();
                    }
                }
            }
        }

        for (std::vector<int>::iterator it2 = fds_to_add.begin(); it2 != fds_to_add.end(); it2++)
        {
            add_pollfd(poll_fds, POLLIN | POLLOUT, *it2);
        }
    }
}

void Server::setCreationDate()
{
    time_t timer;
    struct tm *timeinfo;
    char formated_time[40];

    time(&timer);
    timeinfo = localtime(&timer);
    strftime(formated_time, sizeof(formated_time), "%d-%m-%Y %H:%M:%S", timeinfo);
    this->_creation_date = formated_time;
}

std::string Server::getCreationDate()
{
    return this->_creation_date;
}
Client &Server::getClient(int fd)
{
    if (fd == -1)
    {
        std::map<int, Client>::iterator it = this->_clients.end();
        return it->second;
    }
    std::map<int, Client>::iterator it = this->_clients.find(fd);
    if (it != this->_clients.end())
    {
        return it->second;
    }
    it = this->_clients.end();
    return it->second;
}

Channel &Server::getChannel(std::string name)
{
    if (name == "")
        return *(this->_channels.end());
    if (name[0] != '#')
        name = "#" + name;
    std::vector<Channel>::iterator it = this->_channels.begin();
    for (; it != this->_channels.end(); it++)
    {
        if (it->getName() == name)
        {
            return *it;
        }
    }
    it = this->_channels.end();
    return *it;
}

Client &Server::getClientByNickname(std::string nickname)
{
    std::map<int, Client>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); it++)
    {
        if (it->second.getNickname() == nickname)
        {
            return it->second;
        }
    }
    it = this->_clients.end();
    return it->second;
}

Channel &Server::getChannelByName(std::string name)
{
    if (name == "")
        return *(this->_channels.end());
    if (name[0] != '#')
        name = "#" + name;
    std::vector<Channel>::iterator it = this->_channels.begin();
    for (; it != this->_channels.end(); it++)
    {
        if (it->getName() == name)
        {
            return *it;
        }
    }
    it = this->_channels.end();
    return *it;
}

std::string Server::getPassword()
{
    return this->_password;
}

void Server::setHostname(std::string hostname)
{
    this->_hostname = hostname;
}

std::string Server::getHostname()
{
    return this->_hostname;
}

std::vector<Channel> &Server::getChannels()
{
    return this->_channels;
}