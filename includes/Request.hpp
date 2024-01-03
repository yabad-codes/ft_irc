/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:00:41 by yabad             #+#    #+#             */
/*   Updated: 2024/01/02 12:17:55 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>

class Request {
	private:
		int fd;
		std::string cmd;
		std::string options;
	public:
		Request(int fd);
		void set_cmd(std::string);
		void set_options(std::string);
		int get_fd() const;
		std::string get_cmd() const;
		std::string get_options() const;
};

#endif