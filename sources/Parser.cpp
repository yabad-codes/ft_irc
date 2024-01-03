/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:12:04 by yabad             #+#    #+#             */
/*   Updated: 2024/01/02 12:13:06 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

void Parser::get_command(std::string str, Request* req) {
	size_t del_pos = str.find(" ");
	req->set_cmd(str.substr(0, del_pos));
	if (del_pos == std::string::npos)
		return;
	req->set_options(str.substr(del_pos + 1));
}

Request* Parser::get_request(std::string str, int id) {
	Request* req = new Request(id);

	get_command(str, req);
	return req;
}

void Parser::split_requests(std::queue<Request*>& requests, std::string buffer, const char* del, int id) {
	std::string request;
	size_t del_pos = buffer.find(del);
	while (del_pos != std::string::npos) {
		request = buffer.substr(0, del_pos);
		buffer.erase(0, del_pos + strlen(del));
		requests.push(get_request(request, id));
		del_pos = buffer.find(del);
	}
}

bool Parser::is_valid_request(std::string buffer) {
	size_t len = buffer.size();
	return (buffer[len - 1] == '\n' && buffer[len - 2] == '\r');
}

void Parser::refactor_request(std::string& buffer) {
	buffer.erase(buffer.size() - 1);
	buffer.insert(buffer.size(), "\r\n\0");
}

Parser::Parser(std::queue<Request*>& requests, std::string buffer, int id) {
	if (!is_valid_request(buffer))
		refactor_request(buffer);
	split_requests(requests, buffer, "\r\n", id);
}
