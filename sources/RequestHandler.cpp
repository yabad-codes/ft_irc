/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:41:59 by yabad             #+#    #+#             */
/*   Updated: 2024/01/20 12:53:16 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHandler.hpp"
#include "NickCmd.hpp"
#include "PassCmd.hpp"
#include "UserCmd.hpp"
#include "JoinCmd.hpp"
#include "KickCmd.hpp"
#include "PrivmsgCmd.hpp"
#include "InviteCmd.hpp"
#include "TopiCmd.hpp"
#include "QuitCmd.hpp"

RequestHandler::RequestHandler() {}

ICommand* RequestHandler::identify_cmd(Request* req) {
	if (req->get_cmd() == "NICK")
		return new NickCmd;
	else if (req->get_cmd() == "USER" || req->get_cmd() == "user")
		return new UserCmd;
	else if (req->get_cmd() == "PASS" || req->get_cmd() == "pass")
		return new PassCmd;
	else if (req->get_cmd() == "JOIN")
		return new JoinCmd;
	else if (req->get_cmd() == "KICK")
		return new KickCmd;
	else if (req->get_cmd() == "PRIVMSG")
		return new PrivmsgCmd;
	else if (req->get_cmd() == "INVITE")
		return new InviteCmd;
	else if (req->get_cmd() == "TOPIC")
		return new TopiCmd;
	else if (req->get_cmd() == "QUIT")
		return new QuitCmd;
	return NULL;
}

void RequestHandler::handle_request(Context* context) {
	std::cout << BOLD BRIGHT_CYAN << "[RHINFO] " << RESET << "start handling client(" << context->request->get_fd() << ")'s request" << std::endl;
	ICommand* cmd = identify_cmd(context->request);
	if (cmd != NULL) {
		cmd->execute(context);
		delete cmd;
	}
}