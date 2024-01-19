/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:00:10 by houattou          #+#    #+#             */
/*   Updated: 2024/01/19 16:11:33 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "User.hpp"
#include "Request.hpp"
#include <set>

class Channel 
{
	private:
		std::string name_of_channel;
		std::vector<User *> Users;
		std::set<std::string>oper;
		bool only_invite;
    public:
    	Channel(std::string);
		void set_only_invite(bool);
		bool get_only_invite() const;
    	void add_user_to_channel(User *);
    	std::vector<User *> get_users() const;
		void make_user_operator(std::string);
    	void revoke_operator_status(std::string);
    	std::set<std::string> get_operators() const;
		bool is_exist_user(std::string);
		void kick_user(std::string nickename);
};

