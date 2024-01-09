/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:33 by yabad             #+#    #+#             */
/*   Updated: 2024/01/09 13:10:51 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ICommand.hpp"

enum response_type {
	VAL,
	DUP,
	INV,
	NEW
};

class JoinCmd : public ICommand {
	private:
		response_type type;
		Response* response;
		void create_channel(Context **);
		bool is_valid_channel_name(Context *);
		bool is_duplicate_channel_name(Context *);
		void add_creator_to_channel(Context **);
		std::string convert_name_channel_to_lowercase(std::string name_channel);
	public:
		void execute(Context*);
		int get_type();
		void generate_response(Context*);
};