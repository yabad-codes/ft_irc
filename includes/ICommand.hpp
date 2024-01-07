/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:11:24 by yabad             #+#    #+#             */
/*   Updated: 2024/01/07 16:03:09 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOMMAND_HPP
# define ICOMMAND_HPP

# include "User.hpp"
# include "Request.hpp"
# include "Channel.hpp"
# include "Color.h"
# include <map>

class Context {
	public:
		Request* request;
		User* user;
		std::map<std::string, Channel *> *channels;
};

class ICommand {
	public:
		virtual ~ICommand() {};
		virtual void execute(Context*) const = 0;
		virtual void generate_response() const = 0;
};

#endif