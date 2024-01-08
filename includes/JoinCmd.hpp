/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:33 by yabad             #+#    #+#             */
/*   Updated: 2024/01/07 15:59:40 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ICommand.hpp"

class JoinCmd : public ICommand {
	public:
		void execute(Context*) const;
		void generate_response() const;
};