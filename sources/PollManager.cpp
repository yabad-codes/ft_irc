/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:46:17 by yabad             #+#    #+#             */
/*   Updated: 2024/01/05 18:55:01 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollManager.hpp"

void PollManager::handle_new_connection() {
	struct pollfd client;
	client.fd = accept(server->fd, NULL, NULL);
	if (client.fd == -1) {
		std::cout << BOLD BRIGHT_YELLOW << "[PollManager] " << RESET << "server failed to accept new connection" << RESET << std::endl;
		return;
	}
	User* new_user = new User(client.fd);
	client.events = POLLIN;
	this->pollfds->push_back(client);
	this->users->insert(std::make_pair(client.fd, new_user));
	std::cout << BOLD BRIGHT_BLUE << "[PollManager] " << RESET << "new connection from client with fd : " << client.fd << RESET <<std::endl;
}

void	PollManager::remove_disconnected_client(size_t index)
{
	int client_fd = (*pollfds)[index].fd;
	close(client_fd);
	this->pollfds->erase(this->pollfds->begin() + index);
	std::unordered_map<int, User*>::iterator it = this->users->find(client_fd);
	if (it != this->users->end()) {
		delete it->second;
		this->users->erase(it);
	}
}

void 	PollManager::handle_client_activity(size_t index) {
	char buffer[BUFSIZ];
	int byte_read;

	memset(buffer, '\0', BUFSIZ);
	byte_read = recv((*pollfds)[index].fd, buffer, BUFSIZ, 0);
	if (byte_read == -1)
		std::cout << BOLD BRIGHT_YELLOW << "[PollManager] " << RESET << "error while receiving data from client with fd : " << (*pollfds)[index].fd << RESET << std::endl;
	else if (byte_read == 0)
	{
		std::cout << BOLD BRIGHT_YELLOW << "[PollManager] " << RESET << "client with fd : " << (*pollfds)[index].fd <<" disconnected" << RESET << std::endl;
		remove_disconnected_client(index);
	}
	else
		Parser irc_parser(*requests, buffer, (*pollfds)[index].fd);
}

Context* PollManager::create_context_for_handler(Request* req, User* user, std::map<std::string, Channel*> *channels) {
	Context* context = new Context;
	context->request = req;
	context->user = user;
	context->ch = channels;
	return context;
}

void PollManager::manage_requests() {
	int index = 0;
	while (!this->requests->empty() && index < NREQUESTSTOHANDLE) {
		Request* request = this->requests->front();
		RequestHandler handler;
		try {
			Context* context = create_context_for_handler(request, this->users->find(request->get_fd())->second, this->channel);
			handler.handle_request(context);
			delete context;
		} catch (std::exception& e) {
			//handle exception
		}
		this->requests->pop();
		delete request;
		index++;
	}
}

PollManager::PollManager(server_info* server, std::vector<struct pollfd>& pollfds, std::unordered_map<int, User*>& users, std::queue<Request*>& requests, std::map<std::string, Channel*>&channels) {
	this->server = server;
	this->users = &users;
	this->pollfds = &pollfds;
	this->requests = &requests;
	this->channel = &channels;
	this->pollfds->push_back(pollfd());
	pollfds[0].fd = server->fd;
	pollfds[0].events = POLLIN;
	while (true) {
		if (poll(&pollfds[0], this->pollfds->size(), TIMEOUT) == -1) {
			if (errno == EINTR) {
				std::cout << BOLD BRIGHT_YELLOW << "[PollManager] " << RESET << "poll has been interrupted by a signal" << RESET << std::endl;
				continue;
			}
			throw PMFailureException("[PollManager] poll has been failed");
		}

		if (pollfds[0].revents & POLLIN)
			handle_new_connection();

		for (size_t i = 1; i < this->pollfds->size(); i++) {
			if (pollfds[i].revents & POLLIN)
				handle_client_activity(i);
		}

		manage_requests();
	}
}

PollManager::~PollManager() {}

const char* PollManager::PMFailureException::what() const throw() {
	return msg;
}