/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:50 by yabad             #+#    #+#             */
/*   Updated: 2024/01/03 18:13:28 by yabad            ###   ########.fr       */
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
# include "ConnectionManager.hpp"
# include "PollManager.hpp"
# include "Color.h"

# define TIMEOUT 500
# define NREQUESTSTOHANDLE 3

enum {
	SUCCESS = 0,
	FAILURE	= 1
};

struct server_info {
	int port;
	int	fd;
	std::string password;
	struct sockaddr_in addr;
};

class Server {
	private:
		server_info* server;
		std::vector<struct pollfd> pollfds;
		std::unordered_map<int, User*> users;
		std::queue<Request*> requests;

		void	close_server();
	public:
		Server(int port, std::string password);
		~Server();
};

#endif