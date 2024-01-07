/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:40:11 by yabad             #+#    #+#             */
/*   Updated: 2024/01/07 15:25:05 by yabad            ###   ########.fr       */
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
		std::map<std::string, Channel*> *channels;
		void handle_new_connection();
		void handle_client_activity(size_t);
		void remove_disconnected_client(size_t);
		void manage_requests();
		void send_data(size_t);
		Context* create_context_for_handler(Request*);
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