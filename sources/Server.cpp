/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:56 by yabad             #+#    #+#             */
/*   Updated: 2023/12/24 21:06:45 by yabad            ###   ########.fr       */
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
	std::deque<pollfd> new_client(1);
	int client_socket = accept(server.fd, NULL, NULL);
	if (client_socket != -1)
	{
		new_client[0].fd = client_socket;
		new_client[0].events = POLLIN;
		clients.push_back(new_client[0]);
		std::cout << "[ircserv] New connection from client with fd " << client_socket <<std::endl;
	}
}

void	Server::remove_disconnected_client(int client)
{
	close(clients[client].fd);
	clients.erase(clients.begin() + client);
	
}

void 	Server::handle_client_activity(int client_index)
{
	char buffer[BUFSIZ];
	int byte_read = recv(clients[client_index].fd, buffer, sizeof(buffer), 0);
	if (byte_read == -1)
		throw std::runtime_error("[ircserv] error receiving data from client");
	if (byte_read == 0)
	{
		std::cout<<"[ircserv] client with this fd: " << clients[client_index].fd <<" disconnected" << std::endl;
		remove_disconnected_client(client_index);
	}
	else
	{
		buffer[byte_read] = '\0';
		std::cout << "[ircserv] Received from client " << clients[client_index].fd << ": " << buffer;
	}
}

void	Server::launch(void) 
{
    clients.push_back(pollfd());
	clients[0].fd = server.fd;
	clients[0].events = POLLIN;
	while(true)
	{
		if(poll(&clients[0], clients.size(), - 1) ==  -1)
			throw std::runtime_error("[ircserv] Can't poll");
		if(clients[0].revents & POLLIN)
			handle_new_connection();
		for(size_t i = 1; i < clients.size(); i++)
		{
			if(clients[i].revents & POLLIN)
				handle_client_activity(i);
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
	close(server.fd);
}