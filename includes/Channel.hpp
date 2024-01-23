/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:00:10 by houattou          #+#    #+#             */
/*   Updated: 2024/01/23 10:03:21 by yabad            ###   ########.fr       */
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
		bool has_invited;
		std::string nickname_invited;
		bool seted_topic;
		bool change_topic;
		bool has_set_password;
		std::string password;
		bool has_set_users_limit;
		int number_users_on_channel;
		User *setter_user_topic;
		std::string topic;
		double time;
  public:
    Channel(std::string);
		void  set_time(double);
		double get_time()const;
		std::string get_topic()const;
		void set_topic(std::string);
	  User * get_topic_setter_user()const;
		void set_topic_setter_user(User *);
		void has_set_channel_user_limit(bool);
		bool get_has_channel_user_limit()const;
		void set_number_channel_users_limit(int);
		int get_number_channel_users_limit()const;
		bool number_users_limit_change(int);
		bool is_password_correct(std::string user_input_password);
		void set_password(std::string);
		std::string get_password()const;
		void set_user_password_status(bool);
		bool get_user_password_status()const;
		bool get_change_topic() const;
		void allow_user_to_change_topic(bool);
		void set_only_invite(bool);
		bool get_only_invite() const;
		void set_has_invited(bool);
		bool get_has_seted_topic() const;
		void has_seted_topic(bool);
		bool get_has_invited() const;
		void set_nickname_invited(std::string);
		std::string get_nickname_invited() const;
    void add_user_to_channel(User *);
    std::vector<User *> &get_users();
		void make_user_operator(std::string);
    void revoke_operator_status(std::string);
    std::set<std::string> get_operators() const;
		bool is_exist_user(std::string);
		void kick_user(std::string nickename);
};
