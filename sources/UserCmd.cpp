/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:10:14 by yabad             #+#    #+#             */
/*   Updated: 2024/01/08 16:48:01 by yabad            ###   ########.fr       */
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
	if (params.size() != 4)
		return false;
	user->set_username(params[0]);
	user->set_hostname(params[2]);
	user->set_realname(params[3].substr(1));
	return true;
}

void UserCmd::execute(Context* context) 
{
	this->req = context->request;
	this->user = context->users->find(req->get_fd())->second;
	if (user->is_username_set() || !get_user_params()) {
		generate_response(context);
		return ;
	}
}

void UserCmd::generate_response(Context* context) {
	(void)context;
	std::string res;
	if (user->get_username().size())
		res = ": IRCServ.1337.ma 462 " + user->get_nickname() + " :You may not reregister\r\n";
	else
		res = ": IRCServ.1337.ma 461 * " + user->get_nickname() + " :Not enough parameters\r\n";
	Response* response = new Response(res);
	user->add_response(response);
}