/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:56 by yabad             #+#    #+#             */
/*   Updated: 2023/12/10 14:48:57 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string password) : port(port) {
	(void)password;
	init_server();
}

Server::~Server() {}

void	Server::launch(void) {
	std::cout << "Start accepting new clients." << std::endl;
}

void	Server::init_server(void) {
	std::cout << "[ircserv] Initializing..." << std::endl;
	
	//Create server socket
	server.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server.fd == -1)
		throw std::runtime_error("[ircserv] Can't create socket");
	std::cout << "[ircserv] Server socket created." << std::endl;
	
	//Set up the server address structure
	memset(&server.info, 0, sizeof server.info);
	server.info.sin_family = AF_INET;
	server.info.sin_addr.s_addr = htonl(INADDR_ANY);
	server.info.sin_port = htons(port);
	
	//Set the socket to non-blocking mode
	if (fcntl(server.fd, F_SETFL, O_NONBLOCK) == -1) {
		close_server();
		throw std::runtime_error("[ircserv] Server can't set socket to non-blocking");
	}
	std::cout << "[ircserv] Server socket set to non-blocking mode." << std::endl;
	
	//Bind socket with port
	if (bind(server.fd, reinterpret_cast<struct sockaddr*>(&server.info), sizeof server.info) == -1) {
		close_server();
		throw std::runtime_error("[ircserv] Server can't bind socket");
	}
	std::cout << "[ircserv] Server socket bound with 0.0.0.0:" << port << std::endl;
	
	//Listen with socket for incoming connections
	std::cout << "[ircserv] Is listening and ready to accept new connection..." << std::endl;
	if (listen(server.fd, SOMAXCONN) == -1) {
		close_server();
		throw std::runtime_error("[ircserv] Can't set socket for listening");
	}
}

void	Server::close_server(void) {
	//close server file descriptor
}