#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <poll.h>
#include <vector>

#define PRINT(x) std::cout << x << std::endl;
#define PRINT_ERR(x) std::cerr << x << std::endl;
#define SUCCESS 0
#define FAIL -1
// colors
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

class Server
{
private:
    std::string _creation_date;
    std::string _password;
    std::string _port;
    int _serv_sockfd;
    struct addrinfo *_serv_info;

public:
    Server(std::string password, std::string port);
    ~Server();
    // ************SETTERS************
    void setCreationDate();

    // ************GETTERS************
    std::string getCreationDate();
    struct addrinfo *getServInfo();

    // ************METHODS************
    int networkInit();
    int runLoop();
    int acceptNewConnection();
    int recvMessage(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator it);

    // ************ STATIC FUNCTIONS ************
};
/**
 * @brief Adds a pollfd structure to the given vector.
 *
 * This function adds a pollfd structure to the provided vector of pollfd structures.
 * The pollfd structure represents a file descriptor and the events to be monitored for that descriptor.
 *
 * @param fds The vector of pollfd structures to which the new structure will be added.
 * @param events The events to be monitored for the file descriptor.
 * @param fd The file descriptor to be added to the vector.
 */
void add_pollfd(std::vector<pollfd> &fds, short int events, int fd);
