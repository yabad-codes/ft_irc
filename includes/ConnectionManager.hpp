/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:44:30 by yabad             #+#    #+#             */
/*   Updated: 2024/01/03 15:56:32 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTIONMANAGER_HPP
# define CONNECTIONMANAGER_HPP

# include "Server.hpp"
# include "Color.h"

struct server_info;

class ConnectionManager {
	private:
		server_info* info;
		void create_socket();
		void init_addr_struct();
		void bind_socket();
		void listen_with_socket();
		
	public:
		ConnectionManager(server_info*);
		~ConnectionManager();
		
		class CMFailureException : public std::exception {
			private:
				const char* msg;
			public:
				CMFailureException(const char* message) : msg(message) {};
				const char* what() const throw();
		};
};

#endif