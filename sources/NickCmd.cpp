/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:11:05 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 12:17:20 by yabad            ###   ########.fr       */
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
	User* user = c->users->find(req->get_fd())->second;
	std::string nickname = req->get_options();
	if (!is_first_valid(nickname[0])) {
		generate_response(user, rpl::erroneous_nickname(*user, req->get_options()));
		return true;
	}
	while (nickname[counter] && counter < 9 && is_mid_valid(nickname[counter]))
		counter++;
	req->set_options(req->get_options().substr(0, counter));
	return false;
}

bool NickCmd::is_duplicate(Context* c) {
	Request* req = c->request;
	User* user = c->users->find(req->get_fd())->second;
	std::unordered_map<int, User*>::iterator it = c->users->begin();
	for (; it != c->users->end(); it++) {
		if (req->get_options() == it->second->get_nickname()) {
			generate_response(user, rpl::nick_already_in_use(*user, req->get_options()));
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
	if (!user->is_authenticated()) {
		generate_response(user, rpl::unregistered());
		return ;
	} else {
		if (!user->is_nickname_set()) {
			if (is_nickname_valid(context)) {
				user->set_nickname(req->get_options());
				if (user->is_username_set()) {
					user->set_registered(true);
					generate_response(user, rpl::welcome(*user));
				}
			}
		} else {
			if (req->get_options() == user->get_nickname())
				return ;
			if (is_nickname_valid(context)) {
				generate_response(user, rpl::nickname_set(*user, req->get_options()));
				user->set_nickname(req->get_options());
			}
		}
	}
}

void NickCmd::generate_response(User* user, std::string const response) {
	Response* res = new Response(response);
	user->add_response(res);
}
