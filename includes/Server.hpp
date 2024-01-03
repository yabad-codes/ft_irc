/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:50 by yabad             #+#    #+#             */
/*   Updated: 2024/01/02 19:49:34 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <vector>
# include <iterator>
# include <poll.h>
# include <unistd.h>
# include <queue>
# include <unordered_map>
# include "User.hpp"
# include "Parser.hpp"
# include "Request.hpp"
# include "RequestHandler.hpp"

# define TIMEOUT 500
# define NREQUESTSTOHANDLE 3

enum {
	SUCCESS = 0,
	FAILURE	= 1
};

struct s_socket {
	int	fd;
	struct sockaddr_in info;
};

class Server {
	private:
		int port;
		s_socket server;
		std::vector<struct pollfd> clients;
		std::unordered_map<int, User*> users;
		std::queue<Request*> requests;

		void	init_server();
		void	create_socket();
		void	init_addr_struct();
		void	bind_socket();
		void	listen_with_socket();
		void	close_server();
		void	handle_new_connection();
		void	handle_client_activity(int index);
		void	remove_disconnected_client(int client);
		void	request_handler();
		Context* create_context_for_handler(Request*, User*) const;
	public:
		Server(int port, std::string password);
		~Server();
		void launch();
};

#endif