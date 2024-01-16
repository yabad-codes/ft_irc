/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:41:59 by yabad             #+#    #+#             */
/*   Updated: 2024/01/16 16:46:23 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHandler.hpp"
#include "NickCmd.hpp"
#include "PassCmd.hpp"
#include "UserCmd.hpp"
#include "JoinCmd.hpp"
#include "KickCmd.hpp"
#include "PrivmsgCmd.hpp"

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
	return NULL;
}

void RequestHandler::handle_request(Context* context) {
	ICommand* cmd = identify_cmd(context->request);
	if (cmd != NULL) {
		cmd->execute(context);
		delete cmd;
	}
}