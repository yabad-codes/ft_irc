/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:44:51 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 16:36:26 by yabad            ###   ########.fr       */
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
	std::string const no_such_channel(User& user, std::string channel_name);
	std::string const join_channel(User& user, std::string channel_name);
	std::string const reply_topic(User& user, std::string channel_name, std::string topic);
	std::string const reply_names(User&, std::string, std::string, std::string);
	std::string const reply_end_of_names(User& user, std::string channel_name);
	std::string const reply_channel_mode_is(User& user, std::string channel_name);
}

#endif