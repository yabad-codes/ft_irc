/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:44:40 by houattou          #+#    #+#             */
/*   Updated: 2024/01/18 21:46:01 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

# include "ICommand.hpp"

class JoinCmd : public ICommand 
{
	private:
		std::string channel_name;
	public:
		void create_channel(Context **, std::string channel_name);
		void add_creator_to_channel(Context **, std::string);
		void inform_operators_that_another_user_join_to_channel(User *user, Context *context, std::string &name_channel);
		void execute(Context*);
		void generate_response(User*, std::string const);
		bool is_valid_channel_name(std::string);
		bool is_operator(User *user, Context *context, std::string);
		std::string to_lower(std::string name_channel);
		void set_channel_name(std::string);
		std::string get_channel_name() const;
		void parse_request(std::string request);
		std::string get_members_string(Context *context, Channel *channel, User *user, std::string);
		const char*  user_status_prefix(User *user, Context *context, std::string);
		std::map<std::string, Channel*>::iterator is_exist_channel(Context *context, std::string&);
};
