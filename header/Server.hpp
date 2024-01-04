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
#include <map>
#include "utils.hpp"
#include "irc_replies.hpp"
#include "Client.hpp"
#include "Channel.hpp"

// #define PRINT(x) std::cout << x << std::endl;
// redefine print to not print nothing
#define PRINT(x) ;
#define PRINT_ERR(x) std::cerr << x << std::endl;
#define SUCCESS 0
#define FAIL -1
// colors
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

#define OPER_NAME "admin"
#define OPER_PASS "pass_admin"

class Client;
class Channel;

class Server
{
private:
    std::string _creation_date;
    std::string _password;
    std::string _port;
    std::string _hostname;
    int _serv_sockfd;
    std::map<int, Client> _clients;
    std::vector<Channel> _channels;

public:
    Server();
    Server(std::string password, std::string port);
    ~Server();
    // ************SETTERS************
    void setCreationDate();
    void setHostname(std::string hostname);

    // ************GETTERS************
    std::string getCreationDate();
    std::string getPassword();
    std::string getHostname();
    std::vector<Channel> &getChannels();
    std::map<int, Client> &getClients();

    // ************METHODS************
    int networkInit();
    int runLoop();
    int acceptNewConnection();
    int recvMessage(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator it);
    void removeClient(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator it);
    int parseMessage(int fd);
    Client &getClient(int fd);
    Channel &getChannel(std::string name);
    int registerClient(std::string line, Client &client);
    Client &getClientByNickname(std::string nickname);
    Channel &getChannelByName(std::string name);
    void removeChannel(Channel &channel);
    // ************ STATIC FUNCTIONS ************
};

void add_pollfd(std::vector<pollfd> &fds, short int events, int fd);
