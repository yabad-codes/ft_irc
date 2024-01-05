/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:40:11 by yabad             #+#    #+#             */
/*   Updated: 2024/01/04 19:24:18 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLMANAGER_HPP
# define POLLMANAGER_HPP

# include "Server.hpp"

struct server_info;

class PollManager {
	private:
		server_info* server;
		std::unordered_map<int, User*>* users;
		std::vector<struct pollfd>* pollfds;
		std::queue<Request*>* requests;
		std::map<std::string, Channel*>*channel;
		void handle_new_connection();
		void handle_client_activity(size_t);
		void remove_disconnected_client(size_t);
		void manage_requests();
		Context* create_context_for_handler(Request*, User*, std::map<std::string, Channel*>*);
	public:
		PollManager(server_info*, std::vector<struct pollfd>&, std::unordered_map<int, User*>&, std::queue<Request*>&, std::map<std::string, Channel*>&);
		~PollManager();

		class PMFailureException : public std::exception {
			private:
				const char* msg;
			public:
				PMFailureException(const char* message) : msg(message) {};
				const char* what() const throw();
		};
};

#endif