/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:09:58 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 11:09:18 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <queue>
# include "Response.hpp"

class User {
	private:
		int id;
		std::string nickname;
		std::string username;
		std::string hostname;
		std::string realname;
		bool authenticated;
		bool registered;
		std::queue<Response*> responses;
	public:
		User(int);
		std::string get_nickname() const;
		std::string get_username() const;
		std::string get_hostname() const;
		std::string get_realname() const;
		bool is_authenticated() const;
		bool is_registered() const;
		void set_authenticated(bool);
		void set_registered(bool);
		void set_nickname(const std::string&);
		void set_username(const std::string&);
		void set_hostname(const std::string&);
		void set_realname(const std::string&);
		void add_response(Response*);
		bool has_response() const;
		bool is_username_set() const;
		bool is_nickname_set() const;
		Response* get_next_response();
};

#endif