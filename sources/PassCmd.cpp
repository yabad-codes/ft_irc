/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:05:20 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 10:53:27 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCmd.hpp"

void PassCmd::execute(Context* context) 
{
	Request* req = context->request;
	User* user = context->users->find(req->get_fd())->second;
	std::string server_pass = context->server_info->password;
	if (user->is_authenticated())
		std::cout << BOLD BRIGHT_YELLOW << "[CommandHandler] " << RESET << "Unauthorized command (already authenticated)" << std::endl;
	else if (server_pass == req->get_options()) {
		std::cout << BOLD BRIGHT_BLUE << "[CommandHandler] " << RESET << "Password match (Authenticated)" << std::endl;
		user->set_authenticated(true);
	}
	else {
		std::cout << BOLD BRIGHT_YELLOW << "[CommandHandler]" << RESET << " Incorrect password." << std::endl;
		generate_response(user, rpl::incorrect_server_password());
	}
}

void PassCmd::generate_response(User* user, std::string const response) {
	user->add_response(new Response(response));
}
