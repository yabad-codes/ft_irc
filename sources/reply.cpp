/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:47:42 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 16:37:52 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reply.hpp"

std::string const rpl::welcome001(User& user) {
	std::string reply = SERVER_PREFIX " 001 ";
	reply += user.get_nickname();
	reply += " :Welcome to the Internet Relay Network ";
	reply += user.get_nickname();
	reply += "!";
	reply += user.get_username();
	reply += "@";
	reply += HOSTNAME;
	reply += "\r\n";
	return reply;
}

std::string const rpl::host002(User& user) {
	std::string reply = SERVER_PREFIX " 002 ";
	reply += user.get_nickname();
	reply += " :Your host is ";
	reply += SERVER_NAME;
	reply += ", running version ";
	reply += SERVER_VERSION;
	reply += "\r\n";
	return reply;
}

std::string const rpl::created003(User& user) {
	std::string reply = SERVER_PREFIX " 003 ";
	reply += user.get_nickname();
	reply += " :This server was created ";
	reply += SERVER_CREATION_DATE;
	reply += "\r\n";
	return reply;
}

std::string const rpl::info004(User& user) {
	std::string reply = SERVER_PREFIX " 004 ";
	reply += user.get_nickname();
	reply += " :";
	reply += SERVER_NAME;
	reply += " ";
	reply += SERVER_VERSION;
	reply += USER_MODES;
	reply += " ";
	reply += CHANNEL_MODES;
	reply += "\r\n";
	return reply;
}

std::string const rpl::welcome(User& user) {
	std::string reply = welcome001(user);
	reply += host002(user);
	reply += created003(user);
	reply += info004(user);
	return reply;
}

std::string const rpl::unregistered() {
	std::string reply = SERVER_PREFIX " ";
	reply += "451 ";
	reply += "* :You have not registered";
	reply += "\r\n";
	return reply;
}

std::string const rpl::nickname_set(User& user, std::string new_nickname) {
	std::string reply = ":";
	reply += user.get_nickname();
	reply += "!";
	reply += user.get_username();
	reply += "@";
	reply += HOSTNAME;
	reply += " NICK :";
	reply += new_nickname;
	reply += "\r\n";
	return reply;
}

//:yabad1!_yabad@localhost NICK yabad

std::string const rpl::nick_already_in_use(User& user, std::string new_nickname) {
	std::string reply = SERVER_PREFIX;
	reply += " 433 ";
	reply += user.get_nickname();
	reply += " ";
	reply += new_nickname;
	reply += " :Nickname is already in use.";
	reply += "\r\n";
	return reply;
}

std::string const rpl::erroneous_nickname(User& user, std::string new_nickname) {
	std::string reply = SERVER_PREFIX;
	reply += " 432 ";
	reply += user.get_nickname();
	reply += " ";
	reply += new_nickname;
	reply += " :Erroneous Nickname";
	reply += "\r\n";
	return reply;
}

std::string const rpl::reregister(User& user) {
	std::string reply = SERVER_PREFIX;
	reply += " 462 ";
	reply += user.get_nickname();
	reply += " :You may not reregister";
	reply += "\r\n";
	return reply;
}

std::string const rpl::not_enough_params(User& user) {
	std::string reply = SERVER_PREFIX;
	reply += " 461 ";
	reply += user.get_nickname();
	reply += " :Not enough parameters";
	reply += "\r\n";
	return reply;
}

std::string const rpl::incorrect_server_password() {
	std::string reply = SERVER_PREFIX;
	reply += " 464 * :Password incorrect";
	reply += "\r\n";
	return reply;
}

std::string const rpl::no_such_channel(User& user, std::string channel_name) {
	std::string reply = SERVER_PREFIX " 403 ";
    reply += user.get_nickname() + " " + channel_name;
    reply += " :No such channel\r\n"; 
    return(reply);
}

std::string const rpl::join_channel(User& user, std::string channel_name)
{
    std::string reply = ":";
    reply += user.get_nickname() + "!";
    reply +=  user.get_username() + "@" + HOSTNAME;
    reply += " JOIN :" + channel_name +  "\r\n";
    return(reply);
}

std::string const rpl::reply_topic(User& user, std::string channel_name, std::string topic)
{
    std::string reply = SERVER_PREFIX " 332 ";
    reply += user.get_nickname() + " " + channel_name + " :";
	reply += topic;
	reply += "\r\n";
    return(reply);
}

//user, channel
std::string const rpl::reply_names(User& user, std::string channel_name, std::string state, std::string members)
{
	std::string reply = SERVER_PREFIX " 353 ";
	reply += user.get_nickname();
	reply += " = ";
	reply += channel_name;
	reply += " :";
	reply += state;
	reply += user.get_nickname();
	reply += " ";
	reply += members;
	reply += "\r\n";
	return reply;
}

std::string const rpl::reply_end_of_names(User& user, std::string channel_name)
{
    std::string reply = SERVER_PREFIX " 366 ";
     reply += user.get_nickname();
     reply += " " + channel_name;
     reply += " :End of NAMES list";
	 reply += "\r\n";
     return(reply);
}

std::string const rpl::reply_channel_mode_is(User& user, std::string channel_name)
{
    std::string reply = SERVER_PREFIX " 324 ";
    reply += user.get_nickname() + " " + channel_name + " +";
	reply += "\r\n";
    return(reply);
}