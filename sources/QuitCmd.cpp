/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:49:55 by yabad             #+#    #+#             */
/*   Updated: 2024/01/22 11:00:24 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "QuitCmd.hpp"

void QuitCmd::delete_user_from_pollfds() {
	std::vector<struct pollfd>::iterator it = pollfds->begin();
	for (; it != pollfds->end(); it++) {
		if (req->get_fd() == it->fd) {
			pollfds->erase(it);
			return ;
		}
	}
}

void QuitCmd::delete_user_from_users_list() {
	users->erase(users->find(req->get_fd()));
}

bool QuitCmd::user_in_channel(Channel* channel) {
	std::vector<User*> ch_users = channel->get_users();
	std::vector<User*>::iterator it = ch_users.begin();
	for (; it != ch_users.end(); it++) {
		if (user->get_nickname() == (*it)->get_nickname())
			return true;
	}
	return false;
}

bool QuitCmd::user_in_any_channel() {
	std::map<std::string, Channel*>::iterator it = channels->begin();
	for (; it != channels->end(); it++) {
		if (user_in_channel((*it).second))
			return true;
	}
	return false;
}

void QuitCmd::send_to_all_users(std::vector<User*>& users, std::string res) {
	std::vector<User*>::iterator it = users.begin();
	for (; it != users.end(); it++) {
		if ((*it)->get_nickname() != user->get_nickname())
			(*it)->add_response(new Response(res));
	}
}

void QuitCmd::inform_all_users(std::string reason) {
	std::map<std::string, Channel*>::iterator it = channels->begin();
	std::string res = rpl::quit(*user, reason);
	for (; it != channels->end(); it++) {
		if (user_in_channel(it->second)) {
			send_to_all_users(it->second->get_users(), res);
			it->second->kick_user(user->get_nickname());
		}
	}
}

void QuitCmd::delete_partial_data(int fd) {
	std::map<int, std::string>::iterator it = partial_data->find(fd);
	if (it != partial_data->end()) {
		partial_data->erase(it);
	}
}

void QuitCmd::execute(Context* context) {
	pollfds = context->pollfds;
	req = context->request;
	users = context->users;
	channels = context->channels;
	user = users->find(req->get_fd())->second;
	partial_data = context->partial_data;
	if (user_in_any_channel())
		inform_all_users(req->get_options());
	delete_user_from_pollfds();
	delete_user_from_users_list();
	delete_partial_data(req->get_fd());
	delete user;
	close(req->get_fd());
	std::cout << BOLD BRIGHT_GREEN << "[CHINFO] " << RESET << "client(" << BOLD BRIGHT_CYAN << req->get_fd() << RESET << ") disconnected." << std::endl;
}

void QuitCmd::generate_response(User* user, std::string const response) {
	(void)user, (void)response;
}