/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:05:46 by yabad             #+#    #+#             */
/*   Updated: 2023/12/24 16:51:03 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << "Usage : ./ircserv <port> <password>" << std::endl;
		return FAILURE;
	}
	try {
		int	port = atoi(av[1]);
		std::string password(av[2]);
		Server	app(port, password);
		app.launch();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return FAILURE;
	}
	return SUCCESS;
}