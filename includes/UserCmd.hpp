/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:57:47 by yabad             #+#    #+#             */
/*   Updated: 2024/01/08 16:32:27 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICommand.hpp"

class UserCmd : public ICommand {
	private:
		Request* req;
		User* user;

		std::vector<std::string> my_split(char);
		bool get_user_params();
	public:
		void execute(Context*);
		void generate_response(Context*);
};