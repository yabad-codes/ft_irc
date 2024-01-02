/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:34:39 by yabad             #+#    #+#             */
/*   Updated: 2024/01/02 19:43:38 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHANDLER_HPP
# define REQUESTHANDLER_HPP

# include <iostream>
# include "Request.hpp"
# include "ICommand.hpp"

class RequestHandler {
	private:
		ICommand* identify_cmd(Request*);
	public:
		void handle_request(Context*);
		RequestHandler();
};

#endif