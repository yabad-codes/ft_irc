/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:44:51 by yabad             #+#    #+#             */
/*   Updated: 2024/01/16 17:34:16 by houattou         ###   ########.fr       */
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
	std::string const reply_kick_user(User&, std::string, std::string);
	std::string const reply_are_not_on_channel(User &, std::string, std::string);
	std::string const reply_you_are_not_channel_operator(User&, std::string );
	std::string const no_text_to_send(User& user);
	std::string const privmsg_user(User& sender, User& receiver, std::string message);
	std::string const privmsg_channel(User& sender, std::string receiver, std::string message);
	std::string const no_such_nick(User& user, std::string nickname);
	std::string const cannot_send_to_channel(User& user, std::string channel_name);
}

#endif