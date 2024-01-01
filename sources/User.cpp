/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:47:40 by yabad             #+#    #+#             */
/*   Updated: 2024/01/01 19:09:07 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(int id) {
	this->id = id;
	this->authenticated = false;
	this->registered = false;
}

std::string User::get_nickname() const {
	return this->nickname;
}

std::string User::get_username() const {
	return this->username;
}

bool User::is_authenticated() const {
	return this->authenticated;
}

void User::set_authenticated(bool authenticated) {
	this->authenticated = authenticated;
} 

bool User::is_registered() const {
	return this->registered;
}

void User::set_registered(bool registered) {
	this->registered = registered;
}

void User::set_nickname(const std::string& nickname) {
	this->nickname = nickname;
}

void User::set_username(const std::string& username) {
	this->username = username;	
}
