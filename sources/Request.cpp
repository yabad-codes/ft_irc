/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:02:18 by yabad             #+#    #+#             */
/*   Updated: 2024/01/02 12:17:40 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(int fd) {
	this->fd = fd;
}

void Request::set_cmd(std::string cmd) {
	this->cmd = cmd;
}

void Request::set_options(std::string options) {
	this->options = options;
}

int Request::get_fd() const {
	return this->fd;
}

std::string Request::get_cmd() const {
	return this->cmd;
}

std::string Request::get_options() const {
	return this->options;
}