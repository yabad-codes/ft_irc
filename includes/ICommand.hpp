/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:11:24 by yabad             #+#    #+#             */
/*   Updated: 2024/01/05 18:38:12 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOMMAND_HPP
# define ICOMMAND_HPP

# include "User.hpp"
# include "Request.hpp"
#include "Channel.hpp"
#include<map>

class Context {
	public:
		Request* request;
		User* user;
		Channel *channel;
		std::map<std::string , Channel *>*ch;
	
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
class CreateCmd : public ICommand {
	private:
		void create_channel(Context **)const;
		bool is_valid_channel_name(Context *)const;
		bool is_duplicate_channel_name(Context *)const;
		void add_creator_to_channel(Context **)const;
	public:
		void execute(Context*) const;
};
class JoinCmd : public ICommand 
{
	public:
		void execute(Context*) const;
};
class PrintCmd : public ICommand {
	public:
		void execute(Context*) const;
};
#endif