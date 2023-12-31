/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:47:40 by yabad             #+#    #+#             */
/*   Updated: 2023/12/31 17:09:50 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(int id) {
	this->id = id;
}

const std::string& User::get_nickname() const {
	return this->nickname;
}

const std::string& User::get_username() const {
	return this->username;
}

bool User::is_authenticated() const {
	return this->authenticated;
}

bool User::is_registered() const {
	return this->registered;
}

void User::set_nickname(std::string nickname) {
	this->nickname = nickname;
}

void User::set_username(std::string username) {
	this->username = username;	
}
