/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:08:30 by yabad             #+#    #+#             */
/*   Updated: 2024/01/02 12:06:00 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <queue>
# include "Request.hpp"

class Parser {
	private:
		void split_requests(std::queue<Request*>&, std::string, const char*, int);
		Request* get_request(std::string, int);
		void get_command(std::string, Request*);
		bool is_valid_request(std::string buffer);
		void refactor_request(std::string& buffer);
	public:
		Parser(std::queue<Request*>&, std::string, int);
};

#endif