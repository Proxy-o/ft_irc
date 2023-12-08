#pragma once

#include <string>

#define RPL_WELCOME(hostname, client) (":" + hostname + " 001 " + client + " :Welcome to FT_IRC " + client + "\r\n")
#define RPL_YOURHOST(hostname, client) (":" + hostname + " 002 " + client + " :Your host is CRI, running version 1.0\r\n")
#define RPL_CREATED(hostname, client, date) (":" + hostname + " 003 " + client + " :This server was created " + date + "\r\n")
#define RPL_MYINFO(hostname, client) (":" + hostname + " 004 " + client + " " + "CRI 1.0 io toks k\r\n")
#define RPL_ISUPPORT(hostname, client) (":" + hostname + " 005 " + client + " " + "NICKLEN=9\r\n")

#define ERR_NEEDMOREPARAMS(hostname, client, command) (":" + hostname + " 461 " + client + " " + command + " :Not enough parameters\r\n")
#define ERR_NOTREGISTERED(hostname, client) (":" + hostname + " 451 " + client + " :You have not registered\r\n")

// NICK
#define ERR_NONICKNAMEGIVEN(hostname, nick_name) (":" + hostname + " 431 " + nick_name + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(hostname, client, new_nickname) (":" + hostname + " 432 " + client + " " + new_nickname + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(hostname, client, new_nickname) (":" + hostname + " 433 " + client + " " + new_nickname + " :Nickname is already in use\r\n")
#define RPL_NICK(hostname, old_nick, username, new_nick) (":" + old_nick + "!" + username + "@" + hostname + " NICK " + new_nick + "\r\n")

// PASS
#define ERR_PASSWDMISMATCH(hostname, client) (":" + hostname + " 464 " + client + " :Password incorrect\r\n")
#define ERR_ALREADYREGISTERED(hostname, client) (":" + hostname + " 462 " + client + " :You may not reregister.\r\n")
