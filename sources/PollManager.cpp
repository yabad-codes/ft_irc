/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:46:17 by yabad             #+#    #+#             */
/*   Updated: 2024/01/03 18:26:36 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollManager.hpp"

void PollManager::handle_new_connection(server_info* server, std::unordered_map<int, User*> &users, std::vector<struct pollfd> &pollfds) {
	struct pollfd client;
	client.fd = accept(server->fd, NULL, NULL);
	if (client.fd == -1) {
		std::cout << BOLD BRIGHT_YELLOW << "[PollManager] " << RESET << "server failed to accept new connection" << RESET << std::endl;
		return;
	}
	User* new_user = new User(client.fd);
	client.events = POLLIN;
	pollfds.push_back(client);
	users.insert(std::make_pair(client.fd, new_user));
	std::cout << BOLD BRIGHT_BLUE << "[PollManager] " << RESET << "new connection from client with fd : " << client.fd << RESET <<std::endl;
}

void	PollManager::remove_disconnected_client(std::vector<struct pollfd> &pollfds, std::unordered_map<int, User*> &users, size_t index)
{
	int client_fd = pollfds[index].fd;
	close(client_fd);
	pollfds.erase(pollfds.begin() + index);
	std::unordered_map<int, User*>::iterator it = users.find(client_fd);
	if (it != users.end()) {
		delete it->second;
		users.erase(it);
	}
}

void 	PollManager::handle_client_activity(std::vector<struct pollfd>& pollfds, std::queue<Request*> &requests, std::unordered_map<int, User*> &users, size_t index) {
	char buffer[BUFSIZ];
	int byte_read;

	memset(buffer, '\0', BUFSIZ);
	byte_read = recv(pollfds[index].fd, buffer, BUFSIZ, 0);
	if (byte_read == -1)
		std::cout << BOLD BRIGHT_YELLOW << "[PollManager] " << RESET << "error while receiving data from client with fd : " << pollfds[index].fd << RESET << std::endl;
	else if (byte_read == 0)
	{
		std::cout << BOLD BRIGHT_YELLOW << "[PollManager] " << RESET << "client with fd : " << pollfds[index].fd <<" disconnected" << RESET << std::endl;
		remove_disconnected_client(pollfds, users, index);
	}
	else
		Parser irc_parser(requests, buffer, pollfds[index].fd);
}

PollManager::PollManager(server_info* server, std::vector<struct pollfd>& pollfds, std::unordered_map<int, User*>& users, std::queue<Request*>& requests) {
	pollfds.push_back(pollfd());
	pollfds[0].fd = server->fd;
	pollfds[0].events = POLLIN;
	while (true) {
		if (poll(&pollfds[0], pollfds.size(), TIMEOUT) == -1) {
			if (errno == EINTR) {
				std::cout << BOLD BRIGHT_YELLOW << "[PollManager] " << RESET << "poll has been interrupted by a signal" << RESET << std::endl;
				continue;
			}
			throw PMFailureException("[PollManager] poll has been failed");
		}

		if (pollfds[0].revents & POLLIN)
			handle_new_connection(server, users, pollfds);

		for (size_t i = 1; i < pollfds.size(); i++) {
			if (pollfds[i].revents & POLLIN)
				handle_client_activity(pollfds, requests, users, i);
		}

		//handling requests here
	}
}

PollManager::~PollManager() {}

const char* PollManager::PMFailureException::what() const throw() {
	return msg;
}