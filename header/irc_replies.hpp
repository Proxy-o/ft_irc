#pragma once

#include <string>

# define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters\r\n")


// NICK
# define ERR_NONICKNAMEGIVEN(nick_name) (":localhost 431 " + nick_name + " :No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(client, new_nickname) (":localhost 432 " + client + " " + new_nickname + " :Erroneus nickname\r\n")
# define ERR_NICKNAMEINUSE(client, new_nickname) (":localhost 433 " + client + " " + new_nickname + " :Nickname is already in use\r\n")
# define RPL_NICK(oclient, uclient, client) (":" + oclient + "!" + uclient + "@localhost NICK " +  client + "\r\n")

// PASS
# define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect\r\n")
# define ERR_ALREADYREGISTERED(client) (":localhost 462 " + client + " :You may not reregister.\r\n")
