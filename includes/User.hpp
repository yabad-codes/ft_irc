/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:09:58 by yabad             #+#    #+#             */
/*   Updated: 2024/01/02 18:47:43 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>

class User {
	private:
		int id;
		std::string nickname;
		std::string username;
		bool authenticated;
		bool registered;
		bool is_server_admin;
	public:
		User(int);
		std::string get_nickname() const;
		std::string get_username() const;
		bool is_authenticated() const;
		void set_authenticated(bool);
		bool is_registered() const;
		void set_registered(bool);
		void set_nickname(const std::string&);
		void set_username(const std::string&);
};

#endif