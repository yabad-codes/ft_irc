/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:11:24 by yabad             #+#    #+#             */
/*   Updated: 2024/01/12 17:31:14 by houattou         ###   ########.fr       */
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
// # include "WhoCmd.hpp"
# include <map>

class Context {
	public:
		Request* request;
		std::unordered_map<int, User*> *users;
		std::map<std::string, Channel *> *channels;
};

class ICommand {
	public:
		virtual ~ICommand() {};
		virtual void execute(Context*) = 0;
		virtual void generate_response(Context*) = 0;
};
enum response_type 
{
	CREATOR,
	VAL,
	DUP,
	INVALID_CHANNEL_NAME,
	NEW_CHANNEL,
	JOIN,
	ALREADYINCHANNEL
};

class PrintCmd : public ICommand {
	public:
		void execute(Context*);
		void generate_response(Context*);
};
class WhoCmd : public ICommand 
{
	private:
        response_type type;
        int get_type();
		std::string convert_name_channel_to_lowercase(std::string);
		std::string get_all_users_in_channel(Context *);
        
		Response* response;
		Response* rep_end_of_list;
	public:
		void execute(Context*);
		void generate_response(Context*);
};
class ModeCmd : public ICommand 
{
	private:
		// std::string convert_name_channel_to_lowercase(std::string);
		Response* response;

	public:
		void execute(Context*);
		void generate_response(Context*);
};
#endif
