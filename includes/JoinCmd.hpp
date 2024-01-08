/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:33 by yabad             #+#    #+#             */
/*   Updated: 2024/01/08 12:09:02 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ICommand.hpp"

class JoinCmd : public ICommand {
	public:
		void execute(Context*);
		void generate_response(Context*);
};