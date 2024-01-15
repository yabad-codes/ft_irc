/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:50 by yabad             #+#    #+#             */
/*   Updated: 2024/01/13 12:02:15 by yabad            ###   ########.fr       */
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
# include <cctype>
# include <string>
# include <unordered_map>
# include "User.hpp"
# include "Parser.hpp"
# include "Request.hpp"
# include "RequestHandler.hpp"
# include "ConnectionManager.hpp"
# include "PollManager.hpp"
# include "Color.h"
# include "server_info.hpp"

# define TIMEOUT 500
# define NREQUESTSTOHANDLE 3

enum {
	SUCCESS = 0,
	FAILURE	= 1
};

class Server {
	private:
		server_info* server;
		std::vector<struct pollfd> pollfds;
		std::unordered_map<int, User*> users;
		std::queue<Request*> requests;
		std::map<std::string, Channel*>channels;

		void	close_server();
	public:
		Server(int port, std::string password);
		~Server();
};

#endif