/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:08:30 by yabad             #+#    #+#             */
/*   Updated: 2024/01/01 17:51:39 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <queue>

typedef struct s_request {
	int fd;
	std::string cmd;
	std::string options;
} request;

class Parser {
	private:
		void split_requests(std::queue<request*>&, std::string, const char*, int);
		request* get_request(std::string, int);
		void get_command(std::string, request*);
		bool is_valid_request(std::string buffer);
		void refactor_request(std::string& buffer);
	public:
		Parser(std::queue<request*>&, std::string, int);
};

#endif