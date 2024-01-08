/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:59:41 by yabad             #+#    #+#             */
/*   Updated: 2024/01/08 12:06:25 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ICommand.hpp"

enum res_type {
	VALID,
	DUPLI,
	INVAL
};

class NickCmd : public ICommand {
	private:
		res_type type;
		Response* response;

		bool is_duplicate(Context*);
		bool is_nickname_valid(Context*);
		bool has_invalid_char(Context*);
	public:
		void execute(Context*);
		void generate_response(Context*);
};