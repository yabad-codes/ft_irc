/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:05:46 by yabad             #+#    #+#             */
/*   Updated: 2024/01/21 13:21:16 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "globals.h"

volatile sig_atomic_t keepRunning = true;

void signal_handler(int signum) {
	(void)signum;
	keepRunning = false;
}

int	main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << BOLD BRIGHT_BLUE << "[Usage] : " << BOLD BRIGHT_PURPLE << "./ircserv <port> <password>" << RESET << std::endl;
		return FAILURE;
	}
	signal(SIGINT, signal_handler);
	try {
		Server	app(atoi(av[1]), std::string(av[2]));
	} catch (std::exception &e) {
		std::cerr << BOLD BRIGHT_RED << e.what() << std::endl;
		return FAILURE;
	}
	return SUCCESS;
}