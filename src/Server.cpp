#include "Server.hpp"

Server::Server(std::string password, std::string port) : _password(password), _port(port)
{

    this->setCreationDate();
}

Server::~Server()
{
}

int Server::networkInit()
{
    struct addrinfo hints;
    struct addrinfo *serv_info;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE;     // Listen on any IP address
    int status = getaddrinfo(NULL, _port.c_str(), &hints, &serv_info);
    if (status != 0)
    {
        throw std::runtime_error("getaddrinfo Error");
    }
    this->_serv_sockfd = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);
    if (this->_serv_sockfd == -1)
    {
        throw std::runtime_error("socket Error : can't create socket");
    }
    int yes = 1;
    if (setsockopt(this->_serv_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
    {
        throw std::runtime_error("setsockopt Error: can't set socket options");
    }
    if (bind(this->_serv_sockfd, serv_info->ai_addr, serv_info->ai_addrlen) == -1)
    {
        throw std::runtime_error("bind Error: can't bind socket");
    }
    if (listen(this->_serv_sockfd, 10) == -1)
    {
        throw std::runtime_error("listen Error: can't listen on socket");
    }
    freeaddrinfo(serv_info);
    serv_info = NULL;
    PRINT(RED << "Server is listening on port " << this->_port << RESET);
    return SUCCESS;
}

void add_pollfd(std::vector<pollfd> &fds, short int events, int fd)
{
    pollfd poll_fd;
    poll_fd.fd = fd;
    poll_fd.events = events;
    fds.push_back(poll_fd);
}

int Server::acceptNewConnection()
{
    struct sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_sockfd = accept(this->_serv_sockfd, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_sockfd == -1)
    {
        PRINT_ERR(RED << "accept Error" << RESET);
        return FAIL;
    }
    // TODO: NEED TO ADD NEW CLIENT TO THE CLIENTS LIST
    return client_sockfd;
}

int Server::recvMessage(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator it)
{
    char buffer[1024];
    int recv_status = recv(it->fd, buffer, sizeof(buffer), 0);
    if (recv_status == -1)
    {
        PRINT_ERR(RED << "recv Error" << RESET);
        return FAIL;
    }
    else if (recv_status == 0)
    {
        close(it->fd);
        poll_fds.erase(it);
        PRINT(BLUE << "Client disconnected" << RESET);
        // TODO: NEED TO REMOVE THE CLIENT FROM THE CLIENTS LIST
        return FAIL;
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
                    PRINT(BLUE << "Message received" << RESET);
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
