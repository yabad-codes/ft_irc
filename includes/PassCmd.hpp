/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:51 by yabad             #+#    #+#             */
/*   Updated: 2024/01/15 17:36:09 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCMD_HPP
# define PASSCMD_HPP
# include "ICommand.hpp"

class PassCmd : public ICommand {
	public:
		void execute(Context*);
		void generate_response(User*, std::string const);
};

#endif