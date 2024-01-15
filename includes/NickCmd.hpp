/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:41 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 12:04:25 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ICommand.hpp"

class NickCmd : public ICommand {
	private:
		bool is_duplicate(Context*);
		bool is_nickname_valid(Context*);
		bool has_invalid_char(Context*);
	public:
		void execute(Context*);
		void generate_response(User*, std::string const);
};