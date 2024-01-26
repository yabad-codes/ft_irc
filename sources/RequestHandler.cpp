/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
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
#include "ModeCmd.hpp"
#include "TopiCmd.hpp"
#include "QuitCmd.hpp"

RequestHandler::RequestHandler() {}

/**
 * @brief Identifies the command based on the request and returns an instance of the corresponding ICommand.
 * 
 * @param req The request object containing the command.
 * @return ICommand* A pointer to the ICommand object representing the identified command. Returns NULL if the command is not recognized.
 */
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
	else if (req->get_cmd() == "QUIT")
		return new QuitCmd;
	return NULL;
}

/**
 * @brief Handles a client's request.
 * 
 * This function is responsible for handling a client's request by identifying the command
 * and executing it using the provided context.
 * 
 * @param context The context object containing the client's request.
 */
void RequestHandler::handle_request(Context* context) {
	std::cout << BOLD BRIGHT_CYAN << "[RHINFO] " << RESET << "start handling client(" << context->request->get_fd() << ")'s request" << std::endl;
	ICommand* cmd = identify_cmd(context->request);
	if (cmd != NULL) {
		cmd->execute(context);
		delete cmd;
	}
}