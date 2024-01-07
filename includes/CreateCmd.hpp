/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateCmd.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:07 by yabad             #+#    #+#             */
/*   Updated: 2024/01/07 16:00:41 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ICommand.hpp"

class CreateCmd : public ICommand {
	private:
		void create_channel(Context **)const;
		bool is_valid_channel_name(Context *)const;
		bool is_duplicate_channel_name(Context *)const;
		void add_creator_to_channel(Context **)const;
	public:
		void execute(Context*) const;
		void generate_response() const;
};
