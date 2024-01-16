/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:13:17 by houattou          #+#    #+#             */
/*   Updated: 2024/01/16 17:40:01 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ICommand.hpp"

class KickCmd : public ICommand 
{
	private:
		Response* response;
		std::string channel_name;
		std::string user_name;

	public:
		void execute(Context*);
        void generate_response(User* user, std::string const response);
		void parse_channel_and_user(std::string &request);
		void set_channelname(std::string);
		void set_username(std::string );
		std::string get_channel_name();
		std::string get_username();
		std::map<std::string, Channel *> ::iterator is_exist_channel(Context *context, std::string&);
		std::string reply_kick(User *user, Context *context);
		bool is_operator(User *user, Context *context, std::string channel_name);
		void handle_response_for_kick_user(User* user, std::string user_kicked, std::string channel_name, Channel *channel);
		
};