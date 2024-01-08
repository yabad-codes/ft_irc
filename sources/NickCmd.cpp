/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:11:05 by yabad             #+#    #+#             */
/*   Updated: 2024/01/08 12:16:32 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCmd.hpp"

bool is_first_valid(char c) {
	return (isalpha(c) || c == '_');
}

bool is_mid_valid(char c) {
	return (isalnum(c) || c == '_' || c == '-');
}

bool NickCmd::has_invalid_char(Context* c) {
	size_t counter = 1;
	Request* req = c->request;
	std::string nickname = req->get_options();
	if (!is_first_valid(nickname[0])) {
		this->type = INVAL;
		generate_response(c);
		return true;
	}
	while (nickname[counter] && counter < 9 && is_mid_valid(nickname[counter]))
		counter++;
	req->set_options(req->get_options().substr(0, counter));
	return false;
}

bool NickCmd::is_duplicate(Context* c) {
	Request* req = c->request;
	std::unordered_map<int, User*>::iterator it = c->users->begin();
	for (; it != c->users->end(); it++) {
		if (req->get_options() == it->second->get_nickname()) {
			this->type = DUPLI;
			generate_response(c);
			return true;
		}
	}
	return false;
}

bool NickCmd::is_nickname_valid(Context* context) {
	if (!is_duplicate(context) && !has_invalid_char(context))
		return true;
	return false;
}

void NickCmd::execute(Context* context) {
	Request* req = context->request;
	User* user = context->users->find(req->get_fd())->second;
	if (req->get_options() ==  user->get_nickname())
		return ;
	if (is_nickname_valid(context)) {
		this->type = VALID;
		generate_response(context);
		user->set_nickname(req->get_options());
	}
}

void NickCmd::generate_response(Context* context) {
	std::string res;
	Request* req = context->request;
	User* user = context->users->find(req->get_fd())->second;
	if (this->type == VALID)
		res = ":" + user->get_nickname() + "!" + user->get_username() + "@" + "localhost " + "NICK :" + req->get_options() + "\r\n";
	else if (this->type == DUPLI)
		res = ":IRCServ.1337.ma 433 " + user->get_nickname() + " " + req->get_options() + " :Nickname is already in use.\r\n";
	else
		res = ":IRCServ.1337.ma 432 " + user->get_nickname() + " " + req->get_options() + " :Erroneous Nickname\r\n";
	this->response = new Response(res);
	user->add_response(this->response);
}