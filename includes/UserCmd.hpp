/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:57:47 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 17:36:45 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCMD_HPP
# define USERCMD_HPP
# include "ICommand.hpp"
# define INSUF_PARAMS 1

class UserCmd : public ICommand {
	private:
		Request* req;
		User* user;
		int res_type;

		std::vector<std::string> my_split(char);
		bool get_user_params();
	public:
		void execute(Context*);
		void generate_response(User*, std::string const);
};

#endif