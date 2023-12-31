/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:56 by yabad             #+#    #+#             */
/*   Updated: 2023/12/31 10:19:48 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string password) : port(port) {
	(void)password;
	init_server();
}

Server::~Server() {}

void Server::handle_new_connection()
{
	struct pollfd client;
	client.fd = accept(server.fd, NULL, NULL);
	if (client.fd == -1) {
		std::cout << "[ircserv] server failed to accept new connection." << std::endl;
		return;
	}
	client.events = POLLIN;
	clients.push_back(client);
	std::cout << "[ircserv] new connection from client with fd : " << client.fd <<std::endl;
}

void	Server::remove_disconnected_client(int client)
{
	close(clients[client].fd);
	clients.erase(clients.begin() + client);
}

void 	Server::handle_client_activity(int index)
{
	char buffer[BUFSIZ];
	int byte_read;

	memset(buffer, '\0', BUFSIZ);
	byte_read = recv(clients[index].fd, buffer, BUFSIZ, 0);
	if (byte_read == -1)
		std::cout << "[ircserv] error receiving data from client with fd : " << clients[index].fd << std::endl;
	else if (byte_read == 0)
	{
		std::cout<<"[ircserv] client with fd : " << clients[index].fd <<" disconnected" << std::endl;
		remove_disconnected_client(index);
	}
	else {
		std::cout << "[ircserv] Received from client " << clients[index].fd << ": " << buffer;
		Parser irc_parser(this->requests, buffer, index);
		//handle parsed requests here
	}
}

void	Server::launch(void) 
{
    clients.push_back(pollfd());
	clients[0].fd = server.fd;
	clients[0].events = POLLIN;
	while (true)
	{
		if (poll(&clients[0], clients.size(), TIMEOUT) == -1) {
			if (errno == EINTR)
				continue;
			close_server();
			throw std::runtime_error("[ircserv] poll failed");
		}

		//monitor server for events
		if (clients[0].revents & POLLIN)
			handle_new_connection();

		//monitor clients for events
		for (size_t i = 1; i < clients.size(); i++)
		{
			if (clients[i].revents & POLLIN)
				handle_client_activity(i);
		}

		//clear revents for incoming checks
		for (size_t i = 0; i < clients.size(); i++) {
			if (clients[i].revents)
				clients[i].revents = 0;
		}		
	}
}

//create socket and set it to non-blocking mode
void	Server::create_socket() {
	server.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server.fd == -1)
		throw std::runtime_error("[ircserv] couldn't create socket");
	std::cout << "[ircserv] socket created." << std::endl;

	if (fcntl(server.fd, F_SETFL, O_NONBLOCK) == -1) {
		close_server();
		throw std::runtime_error("[ircserv] couldn't set socket to non-blocking mode");
	}
	std::cout << "[ircserv] socket set to non-blocking mode." << std::endl;
}

//bind socket with ip address and port
void	Server::bind_socket() {
	if (bind(server.fd, reinterpret_cast<struct sockaddr*>(&server.info), sizeof server.info) == -1) {
		close_server();
		throw std::runtime_error("[ircserv] couldn't bind socket");
	}
	std::cout << "[ircserv] socket bound with 0.0.0.0:" << port << std::endl;
}

//listening through socket
void	Server::listen_with_socket() {
	std::cout << "[ircserv] is listening and ready to accept new connections..." << std::endl;
	if (listen(server.fd, SOMAXCONN) == -1) {
		close_server();
		throw std::runtime_error("[ircserv] couldn't set socket for listening");
	}
}

void	Server::init_addr_struct() {
	memset(&server.info, 0, sizeof server.info);
	server.info.sin_family = AF_INET;
	server.info.sin_addr.s_addr = htonl(INADDR_ANY);
	server.info.sin_port = htons(port);	
}

void	Server::init_server(void) {
	std::cout << "[ircserv] initializing..." << std::endl;
	
	create_socket();
	init_addr_struct();
	bind_socket();
	listen_with_socket();
}

void	Server::close_server(void) {
	std::vector<struct pollfd>::iterator it;

	for (it = clients.begin(); it != clients.end(); it++) {
		close((*it).fd);
	}
}