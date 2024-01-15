/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:33 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 14:14:53 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ICommand.hpp"

class JoinCmd : public ICommand {
	private:
		response_type type;
		Response* response;

		void create_channel(Context **);
		bool is_valid_channel_name(Context *);
		void add_creator_to_channel(Context **);
		std::string join_channel(User *user, std::string &name_channel);
		std::string no_such_channel(User *user, std::string &name_channel);
		std::string convert_name_channel_to_lowercase(std::string name_channel);
		std::map<std::string, Channel*> ::iterator is_exist_channel(Context *context);
		
		std::string  user_status_prefix(User *user, Context *context );
		bool is_operator(User *user, Context *context);
		std::string create_initial_members_string(Context *context, User *user,std::string  user_status_prefix);
		std::string append_users_to_members_string(Context *context, Channel *channel, User *user, std::string & members);
		std::string reply_names(Context *context);
		std::string reply_end_of_names(User *user, std::string &name_channel);
		std::string reply_channel_mode_is(User *user, std::string& name_channel);
		std::string reply_topic(User *user, std::string & name_channel);
		void inform_operators_that_another_user_join_to_channel(User *user, Context *context, std::string &name_channel);
		void execute(Context*);
		int get_type();
		void generate_response(Context*);
};