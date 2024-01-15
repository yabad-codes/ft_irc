/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:11:24 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 10:54:25 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOMMAND_HPP
# define ICOMMAND_HPP

# include <unordered_map>
# include "User.hpp"
# include "Request.hpp"
# include "Channel.hpp"
# include "Color.h"
# include "Response.hpp"
# include <map>
# include "server_info.hpp"
# include "reply.hpp"

class Context {
	public:
		Request* request;
		std::unordered_map<int, User*> *users;
		std::map<std::string, Channel *> *channels;
		server_info* server_info;
};

class ICommand {
	public:
		virtual ~ICommand() {};
		virtual void execute(Context*) = 0;
		virtual void generate_response(User*, std::string const) = 0;
};

#endif