/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:41 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 17:35:46 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICKCMD_HPP
# define NICKCMD_HPP
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

#endif