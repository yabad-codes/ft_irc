/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:56 by yabad             #+#    #+#             */
/*   Updated: 2023/12/11 20:35:58 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string password) : port(port) {
	(void)password;
	init_server();
}

Server::~Server() {}

void Server::Handle_NewConnection()
{
	std::vector<pollfd> NewClient(1);
	int clientSocket = accept(server.fd, NULL, NULL);
	if (clientSocket != -1)
	{
		
		NewClient[0].fd = clientSocket;
		NewClient[0].events = POLLIN;
		clients.push_back(NewClient[0]);
		std::cout << "[ircserv] New connection from client with fd " << clientSocket <<std::endl;
	}
}

void	Server::remove_disconnected_client(int client)
{
	close(clients[client].fd);
	clients.erase(clients.begin() +client);
	
}

void 	Server::HandleClientActivity(int client_index)
{
	char buffer[BUFSIZ];
	int byteRead = recv(clients[client_index].fd, buffer, sizeof(buffer), 0);
	if (byteRead == -1)
		throw std::runtime_error("[ircserv] error receiving data from client");
	if (byteRead == 0)
	{
		std::cout<<"[ircserv] client with this fd: " << clients[client_index].fd <<" disconnected" << std::endl;
		remove_disconnected_client(client_index);
	}
	else
	{
		buffer[byteRead] = '\0';
		std::cout << "[ircserv] Received from client " << clients[client_index].fd << ": " << buffer;
	}
}

void	Server::launch(void) 
{
	std::cout << "[ircserv] Server is running and ready to accept new connections..." << std::endl;
    clients.push_back(pollfd()); 
	clients[0].fd = server.fd;
	clients[0].events = POLLIN;
	while(1)
	{
		if(poll(&clients[0], clients.size(), - 1) ==  -1)
			throw std::runtime_error("[ircserv] Can't poll");
		if(clients[0].revents & POLLIN)
			Handle_NewConnection();
		for(size_t i = 1; i < clients.size(); i++)
		{
			if(clients[i].revents & POLLIN)
				HandleClientActivity(i);
		}
	}
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