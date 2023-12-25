#pragma once

#include "Server.hpp"
#include "Client.hpp"

void nick(std::string &line, Client &client, Server &server);
void user(std::string &message, Client &client, Server &server);
void pass(std::string &message, Client &client, Server &server);
void oper(std::string &message, Client &client, Server &server);
void privmsg(std::string &message, Client &client, Server &server);
void ping_pong(std::string &message, Client &client);
void topic(std::string &message, Client &client, Server &server);
void kick(std::string &message, Client &client, Server &server);
// channel commands
void join(std::string &message, Client &client, Server &server);