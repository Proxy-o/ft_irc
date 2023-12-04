#include "Server.hpp"

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
    poll_fds.erase(it);
    this->_clients.erase(it->fd);
    PRINT(BLUE << "Client disconnected" << RESET);
}

void Server::setClientRecvBuffer(std::vector<pollfd>::iterator it, std::string message)
{
    Client &client = this->getClient(it->fd);
    client.setRecvBuffer(message);
    
}
int Server::recvMessage(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator it)
{
    char buffer[512];
    bzero(buffer, sizeof(buffer));
    int recv_status = recv(it->fd, buffer, sizeof(buffer), 0);
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
        setClientRecvBuffer(it, message);
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

        std::vector<pollfd>::iterator it = poll_fds.begin();
        for (; it != poll_fds.end(); it++)
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
        }
        std::vector<int>::iterator it2 = fds_to_add.begin();
        for (; it2 != fds_to_add.end(); it2++)
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
    std::map<int, Client>::iterator it = this->_clients.find(fd);
    if (it != this->_clients.end())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("Client not found");
    }
}