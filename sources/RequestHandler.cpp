/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/01/19 17:24:44 by houattou         ###   ########.fr       */
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
#include "ModeCmd.hpp"
#include "TopiCmd.hpp"

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
	else if (req->get_cmd() == "MODE")
		return new ModeCmd;
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