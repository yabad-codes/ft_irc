/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:05:46 by yabad             #+#    #+#             */
/*   Updated: 2024/01/19 11:57:34 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << BOLD BRIGHT_BLUE << "[Usage] : " << BOLD BRIGHT_PURPLE << "./ircserv <port> <password>" << RESET << std::endl;
		return FAILURE;
	}
	try {
		Server	app(atoi(av[1]), std::string(av[2]));
	} catch (std::exception &e) {
		std::cerr << BOLD BRIGHT_RED << e.what() << std::endl;
		return FAILURE;
	}
	return SUCCESS;
}