/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:12:04 by yabad             #+#    #+#             */
/*   Updated: 2023/12/30 14:41:02 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

void Parser::get_command(std::string str, request* req) {
	size_t del_pos = str.find(" ");
	req->cmd = str.substr(0, del_pos);
	if (del_pos == std::string::npos)
		return;
	req->options = str.substr(del_pos + 1);
}

request* Parser::get_request(std::string str, int id) {
	request* req = new request;

	req->fd = id;
	get_command(str, req);
	return req;
}


void Parser::split_requests(std::queue<request*>& requests, std::string buffer, const char* del, int id) {
	std::string request;
	size_t del_pos = buffer.find(del);
	while (del_pos != std::string::npos) {
		request = buffer.substr(0, del_pos);
		buffer.erase(0, del_pos + strlen(del));
		requests.push(get_request(request, id));
		del_pos = buffer.find(del);
	}
}

Parser::Parser(std::queue<request*>& requests, std::string buffer, int id) {
	split_requests(requests, buffer, "\r\n", id);
}
