/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:41:59 by yabad             #+#    #+#             */
/*   Updated: 2024/01/09 13:22:45 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHandler.hpp"
#include "NickCmd.hpp"
#include "PassCmd.hpp"
#include "UserCmd.hpp"
#include "JoinCmd.hpp"

RequestHandler::RequestHandler() {}

ICommand* RequestHandler::identify_cmd(Request* req) {
	std::cout <<"get_cmd : " << req->get_cmd() << std::endl;
	if (req->get_cmd() == "NICK")
		return new NickCmd;
	else if (req->get_cmd() == "USER")
		return new UserCmd;
	else if (req->get_cmd() == "PASS")
		return new PassCmd;
	else if (req->get_cmd() == "JOIN")
		return new JoinCmd;
	else if (req->get_cmd() == "Print")
		return new PrintCmd;
	else if (req->get_cmd() == "WHO")
		return new WHOCmd;					
	return NULL;
	//if else if else and return the appropriate type
}

void RequestHandler::handle_request(Context* context) {
	ICommand* cmd = identify_cmd(context->request);
	if (cmd != NULL) {
		cmd->execute(context);
		delete cmd;
	}
}