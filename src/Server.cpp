#include "Server.hpp"
#include "Client.hpp"

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
    close(it->fd);
    this->_clients.erase(it->fd);
    poll_fds.erase(it);
    PRINT(BLUE << "Client disconnected" << RESET);
}

int Server::recvMessage(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator it)
{
    char buffer[513];
    bzero(buffer, sizeof(buffer));
    int recv_status = recv(it->fd, buffer, sizeof(buffer) - 1, 0);
    if (recv_status == -1)
    {
        PRINT_ERR(RED << "recv Error" << RESET);
        return FAIL;
    }
    else if (recv_status == 0)
    {

        removeClient(poll_fds, it);
        return FAIL;
    }
    else
    {
        std::string message(buffer);
        Client &client = this->getClient(it->fd);
        client.setRecvBuffer(message);
        PRINT(YELLOW << "CLIENT : " << client.getRecvBuffer() << RESET);
        return SUCCESS;
    }

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