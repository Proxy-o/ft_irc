#pragma once

#include "Server.hpp"
#include "Client.hpp"

void nick(std::string &line, Client &client, Server &server);
void user(std::string &message, Client &client);
void pass(std::string &message, Client &client, Server &server);
void oper(std::string &message, Client &client);
void privmsg(std::string &message, Client &client, Server &server);