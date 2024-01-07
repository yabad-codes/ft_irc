/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:30:29 by yabad             #+#    #+#             */
/*   Updated: 2024/01/07 15:50:26 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(std::string res) {
	this->response = res;
}

Response::~Response() {}

const char* Response::get_response() const {
	return this->response.c_str();
}

size_t Response::get_size() const {
	return this->response.size();
}