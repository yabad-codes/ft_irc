/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:10:14 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 11:17:50 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserCmd.hpp"

std::vector<std::string> UserCmd::my_split(char del) {
	std::vector<std::string> vect;
	std::string options = req->get_options();
	size_t del_pos = 0;
	size_t start_pos = 0;
	do {
		del_pos = options.find(del, start_pos);
		std::string str = options.substr(start_pos, del_pos - start_pos);
		vect.push_back(str);
		start_pos = del_pos + 1;
	}
	while (del_pos != std::string::npos);
	return vect;
}

bool UserCmd::get_user_params() {
	std::vector<std::string> params = my_split(' ');
	if (params.size() != 4) {
		res_type = INSUF_PARAMS;
		return false;
	}
	user->set_username(params[0]);
	user->set_hostname(params[2]);
	user->set_realname(params[3].substr(1));
	if (user->is_nickname_set()) {
		user->set_registered(true);
		generate_response(user, rpl::welcome(*user));
	}
	return true;
}

void UserCmd::execute(Context* context) 
{
	this->req = context->request;
	this->user = context->users->find(req->get_fd())->second;
	if (!user->is_authenticated())
		generate_response(user, rpl::unregistered());
	else if (user->is_username_set() || !get_user_params()) {
		if (res_type != INSUF_PARAMS) {
			generate_response(user, rpl::reregister(*user));
			return ;
		}
		generate_response(user, rpl::not_enough_params(*user));
	}
}

void UserCmd::generate_response(User* user, std::string const response) {
	Response* res = new Response(response);
	user->add_response(res);
}