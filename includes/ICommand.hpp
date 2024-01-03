/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:11:24 by yabad             #+#    #+#             */
/*   Updated: 2024/01/02 19:48:23 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOMMAND_HPP
# define ICOMMAND_HPP

# include "User.hpp"
# include "Request.hpp"

class Context {
	public:
		Request* request;
		User* user;
		//Channel* channel;
		//maybe other data needed
};

class ICommand {
	public:
		virtual ~ICommand() {};
		virtual void execute(Context*) const = 0;
};

class PassCmd : public ICommand {
	public:
		void execute(Context*) const;
};

class NickCmd : public ICommand {
	public:
		void execute(Context*) const;
};

class UserCmd : public ICommand {
	public:
		void execute(Context*) const;
};

#endif