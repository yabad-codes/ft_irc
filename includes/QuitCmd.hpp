/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:47:53 by yabad             #+#    #+#             */
/*   Updated: 2024/01/22 10:54:49 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUITCMD_HPP
# define QUITCMD_HPP

# include "ICommand.hpp"

class QuitCmd : public ICommand {
	private:
		std::vector<struct pollfd>* pollfds;
		Request* req;
		User* user;
		std::map<std::string, Channel*> *channels;
		std::unordered_map<int, User*> *users;
		std::map<int, std::string> *partial_data;

		void send_to_all_users(std::vector<User*>&, std::string);
		void inform_all_users(std::string reason);
		bool user_in_channel(Channel*);
		bool user_in_any_channel();
		void delete_user_from_pollfds();
		void delete_user_from_users_list();
		void delete_partial_data(int);
	public:
		void execute(Context*);
		void generate_response(User*, std::string const);	
};

#endif