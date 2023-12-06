#pragma once

#include "Server.hpp"
#include "Client.hpp"

void nick(std::string &line, Client &client, Server &server);
void user(std::string &message, Client &clientr);