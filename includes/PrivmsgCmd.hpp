/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCmd.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:10:53 by yabad             #+#    #+#             */
/*   Updated: 2024/01/16 16:53:46 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSGCMD_HPP
# define PRIVMSGCMD_HPP

# include "ICommand.hpp"

enum receiver_type {
	USER,
	CHANNEL
};

class PrivmsgCmd : public ICommand {
	private:
		std::string receiver;
		receiver_type type;
		User* receiv;
		Channel* channel;
		std::string message;

		bool find_receiver(Context*);
		bool find_channel(Context*);
		bool parse_request(Request*);
		bool is_sender_in_channel(User*, std::vector<User*>);
		void send_message_to_channel(User*, std::string, Channel*);
		void set_receiver_type(std::string);
	public:
		void execute(Context*);
		void generate_response(User*, std::string const);
};

#endif