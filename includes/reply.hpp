/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:44:51 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 12:50:15 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
# define REPLY_HPP

# include <iostream>
# include "User.hpp"
# include "server_info.hpp"

namespace rpl {
	std::string	const welcome(User& user);
	std::string const welcome001(User& user);
	std::string const host002(User& user);
	std::string const created003(User& user);
	std::string const info004(User& user);
	std::string const unregistered();
	std::string const nickname_set(User& user, std::string new_nickname);
	std::string const nick_already_in_use(User& user, std::string new_nickname);
	std::string const erroneous_nickname(User& user, std::string new_nickname);
	std::string const reregister(User& user);
	std::string const not_enough_params(User& user);
	std::string const incorrect_server_password();
}

#endif