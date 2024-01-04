#include "Server.hpp"
#include "Client.hpp"

int Server::networkInit()
{
    struct addrinfo hints;
    struct addrinfo *serv_info;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE;     // Listen on any IP address
    int status = getaddrinfo(NULL, this->_port.c_str(), &hints, &serv_info);
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
    Client client(client_sockfd);
    this->_clients.insert(std::pair<int, Client>(client_sockfd, client));
    return client_sockfd;
}