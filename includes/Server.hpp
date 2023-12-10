/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:47:50 by yabad             #+#    #+#             */
/*   Updated: 2023/12/10 14:53:43 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <fcntl.h>

struct s_socket {
	int	fd;
	struct sockaddr_in info;
};

class Server {
	private:
		int port;
		s_socket server;

		void	init_server(void);
		void	close_server(void);
	public:
		Server(int port, std::string password);
		~Server();
		void launch(void);
};

#endif