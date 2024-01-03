/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:56 by yabad             #+#    #+#             */
/*   Updated: 2024/01/03 17:47:35 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string password) {
	this->server = new server_info;
	this->server->password = password;
	this->server->port = port;
	try {
		ConnectionManager* connectionManager = new ConnectionManager(this->server);
		PollManager* pollManager = new PollManager(server, pollfds, users, requests);
		(void)connectionManager, (void)pollManager;
	} catch (std::exception& e) {
		std::cout << BOLD BRIGHT_RED << e.what() << RESET << std::endl;
		close_server();
	}
}

Server::~Server() {}

//still need to update it to free all memory allocated if necessary
void	Server::close_server(void) {
	std::vector<struct pollfd>::iterator it;

	for (it = pollfds.begin(); it != pollfds.end(); it++) {
		close((*it).fd);
	}
	//lets exit for now
	exit(EXIT_FAILURE);
}
