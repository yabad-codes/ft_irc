/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:33 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 17:35:29 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCMD_HPP
# define JOINCMD_HPP

# include "ICommand.hpp"

class JoinCmd : public ICommand {
	private:
		void create_channel(Context **);
		void add_creator_to_channel(Context **);
		void inform_operators_that_another_user_join_to_channel(User *user, Context *context, std::string &name_channel);
		void execute(Context*);
		void generate_response(User*, std::string const);
		bool is_valid_channel_name(Context *);
		bool is_operator(User *user, Context *context);
		std::string to_lower(std::string name_channel);
		std::string get_members_string(Context *context, Channel *channel, User *user);
		const char*  user_status_prefix(User *user, Context *context);
		std::map<std::string, Channel*>::iterator is_exist_channel(Context *context);
};

#endif