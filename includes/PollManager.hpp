/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:40:11 by yabad             #+#    #+#             */
/*   Updated: 2024/01/03 18:26:27 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLMANAGER_HPP
# define POLLMANAGER_HPP

# include "Server.hpp"

struct server_info;

class PollManager {
	private:
		void handle_new_connection(server_info*, std::unordered_map<int, User*>&, std::vector<struct pollfd>&);
		void handle_client_activity(std::vector<struct pollfd>&, std::queue<Request*>&, std::unordered_map<int, User*>&, size_t);
		void remove_disconnected_client(std::vector<struct pollfd>&, std::unordered_map<int, User*>&, size_t);
	public:
		PollManager(server_info*, std::vector<struct pollfd>&, std::unordered_map<int, User*>&, std::queue<Request*>&);
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