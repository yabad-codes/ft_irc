/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:09:58 by yabad             #+#    #+#             */
/*   Updated: 2023/12/31 17:42:38 by yabad            ###   ########.fr       */
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
	public:
		User(int);
		const std::string& get_nickname() const;
		const std::string& get_username() const;
		bool is_authenticated() const;
		bool is_registered() const;
		void set_nickname(std::string);
		void set_username(std::string);
};

#endif