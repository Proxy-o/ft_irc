#pragma once

#include <string>

#define RPL_WELCOME(hostname, client) (":" + hostname + " 001 " + client + " :Welcome to FT_IRC " + client + "\r\n")
#define RPL_YOURHOST(hostname, client) (":" + hostname + " 002 " + client + " :Your host is CRI, running version 1.0\r\n")
#define RPL_CREATED(hostname, client, date) (":" + hostname + " 003 " + client + " :This server was created " + date + "\r\n")
#define RPL_MYINFO(hostname, client) (":" + hostname + " 004 " + client + " " + "CRI 1.0 io toks k\r\n")
#define RPL_ISUPPORT(hostname, client) (":" + hostname + " 005 " + client + " " + "NICKLEN=9\r\n")

// OPER
#define RPL_YOUREOPER(hostname, client) (":" + hostname + " 381 " + client + " :You are now an IRC operator\r\n")

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

// PRIVMSG
#define ERR_NOSUCHNICK(hostname, client, nickname) (":" + hostname + " 401 " + client + " " + nickname + " :No such nick/channel\r\n")
#define PRIVMSG(hostname, client, username, target, message) (":" + client + "!~" + username + "@" + hostname + " PRIVMSG " + target + " " + message + "\r\n")


// JOIN
#define ERR_NOSUCHCHANNEL(hostname, client, channel_name) (":" + hostname + " 403 " + client + " " + channel_name + " :No such channel\r\n")
//:hnait!~hnait@42EDF57F.D77B4111.FCEB539D.IP JOIN :#cha1
#define RPL_JOIN(clientname, clientnick, hostname, channel_name) (":" + clientname + "!~" +clientnick + hostname + " JOIN :" + channel_name + "\r\n")
#define RPL_MODE(hostname, channel_name, modes) (":" + hostname + " MODE " + channel_name + " " + modes + "\r\n")
#define RPL_NAMREPLY(hostname, client, channel_name, nicknames) (":" + hostname + " 353 " + client + " = " + channel_name + " :" + nicknames + "\r\n")
#define RPL_ENDOFNAMES(hostname, client, channel_name) (":" + hostname + " 366 " + client + " " + channel_name + " :End of NAMES list\r\n")
