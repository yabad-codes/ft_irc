/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:13:16 by yabad             #+#    #+#             */
/*   Updated: 2024/01/16 17:04:11 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivmsgCmd.hpp"

void PrivmsgCmd::set_receiver_type(std::string receiver) {
	if (receiver[0] == '#') {
		type = CHANNEL;
		return ;
	}
	type = USER;
}

bool PrivmsgCmd::parse_request(Request* req) {
	std::string str = req->get_options();
	size_t del_pos = str.find(':');
	if (del_pos == std::string::npos)
		return false;
	receiver = str.substr(0, del_pos - 1);
	message = str.substr(del_pos + 1);
	set_receiver_type(receiver);
	return true;
}

bool PrivmsgCmd::find_receiver(Context* context) {
	std::unordered_map<int, User*>::iterator it = context->users->begin();
	for (; it != context->users->end(); it++) {
		if (receiver == it->second->get_nickname()) {
			receiv = it->second;
			return true;
		}
	}
	return false;
}

bool PrivmsgCmd::find_channel(Context* context) {
	std::map<std::string, Channel*>::iterator it = context->channels->begin();
	for (; it != context->channels->end(); it++) {
		if (receiver == it->first) {
			channel = it->second;
			return true;
		}
	}
	return false;
}

bool PrivmsgCmd::is_sender_in_channel(User* sender, std::vector<User*> users) {
	std::vector<User*>::iterator it = users.begin();
	for (; it != users.end(); it++) {
		if (sender->get_nickname() == (*it)->get_nickname())
			return true;
	}
	return false;
}

void PrivmsgCmd::send_message_to_channel(User* sender, std::string message, Channel* channel) {
	std::vector<User*> users = channel->get_users();
	std::vector<User*>::iterator it = users.begin();
	for (; it != users.end(); it++) {
		if (sender->get_nickname() != (*it)->get_nickname())
			generate_response(*it, message);
	}
}

void PrivmsgCmd::execute(Context* context) {
	Request* req = context->request;
	User* sender = context->users->find(req->get_fd())->second;
	if (!sender->is_authenticated()) {
		generate_response(sender, rpl::unregistered());
		return ;
	}
	if (parse_request(req) == false) {
		generate_response(sender, rpl::no_text_to_send(*sender));
		return ;
	}
	if (type == USER) {
		if (find_receiver(context))
			generate_response(receiv, rpl::privmsg_user(*sender, *receiv, message));
		else
			generate_response(sender, rpl::no_such_nick(*sender, receiver));
		return ;
	}
	if (find_channel(context)) {
		if (is_sender_in_channel(sender, channel->get_users()))
			send_message_to_channel(sender, rpl::privmsg_channel(*sender, receiver, message), channel);
		else
			generate_response(sender, rpl::cannot_send_to_channel(*sender, receiver));
		return ;
	}
	generate_response(sender, rpl::no_such_channel(*sender, receiver));
}

void PrivmsgCmd::generate_response(User* user, std::string const response) {
	user->add_response(new Response(response));
}