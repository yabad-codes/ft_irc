/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:46:20 by yabad             #+#    #+#             */
/*   Updated: 2024/01/19 12:29:06 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionManager.hpp"

ConnectionManager::ConnectionManager(server_info* info) {
	std::cout << BOLD BRIGHT_BLUE << "[CMINFO]" << RESET << " initializing server..." << RESET << std::endl;
	this->info = info;
	
	try {
		create_socket();
		init_addr_struct();
		bind_socket();
		listen_with_socket();
	} catch (std::exception& e) {
		throw CMFailureException(e.what());
	}
}

ConnectionManager::~ConnectionManager() {}

void	ConnectionManager::create_socket() {
	info->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (info->fd == -1)
		throw std::runtime_error("[CMERROR] couldn't create server socket");
	std::cout << BOLD BRIGHT_BLUE << "[CMINFO]" << RESET << " server socket created" << RESET << std::endl;

	if (fcntl(info->fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("[CMERROR] couldn't set server socket to non-blocking mode");
	std::cout << BOLD BRIGHT_BLUE << "[CMINFO]" << RESET << " server socket set to non-blocking mode" << RESET << std::endl;
}

void	ConnectionManager::bind_socket() {
	if (bind(info->fd, reinterpret_cast<struct sockaddr*>(&info->addr), sizeof info->addr) == -1)
		throw std::runtime_error("[CMERROR] couldn't bind server socket (probably the port is already in use)");
	std::cout << BOLD BRIGHT_BLUE << "[CMINFO]" << RESET << " server socket bound with 0.0.0.0:" << info->port << RESET << std::endl;
}

void	ConnectionManager::listen_with_socket() {
	std::cout << BOLD BRIGHT_BLUE << "[CMINFO]" << RESET << " server socket is listening and ready to accept new connections..." << RESET << std::endl;
	if (listen(info->fd, SOMAXCONN) == -1)
		throw std::runtime_error("[CMERROR] couldn't set socket for listening");
}

void	ConnectionManager::init_addr_struct() {
	memset(&info->addr, 0, sizeof info->addr);
	info->addr.sin_family = AF_INET;
	info->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	info->addr.sin_port = htons(info->port);
}

const char* ConnectionManager::CMFailureException::what() const throw() {
	return msg;
}
