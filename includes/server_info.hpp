/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_info.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:00:02 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 11:43:50 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_INFO_HPP
# define SERVER_INFO_HPP

# include <iostream>
# include <netinet/in.h>

# define SERVER_PREFIX ":ircserv.1337.ma"
# define SERVER_NAME "ircserv"
# define SERVER_VERSION "0.01"
# define SERVER_CREATION_DATE "08/01/2024"
# define HOSTNAME "localhost"
# define USER_MODES "io"
# define CHANNEL_MODES "i"

struct server_info {
	int port;
	int	fd;
	std::string password;
	struct sockaddr_in addr;
};

#endif