/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:50 by yabad             #+#    #+#             */
/*   Updated: 2023/12/11 20:39:00 by houattou         ###   ########.fr       */
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
# include <poll.h>
# include <unistd.h>

struct s_socket {
	int	fd;
	struct sockaddr_in info;
};

class Server {
	private:
		int port;
		s_socket server;
		std::vector<struct pollfd> clients;

		void	init_server(void);
		void	close_server(void);
		void	Handle_NewConnection(void);
		void	HandleClientActivity(int index);
		void	remove_disconnected_client(int client);
	public:
		Server(int port, std::string password);
		~Server();
		void launch(void);
	
};

#endif