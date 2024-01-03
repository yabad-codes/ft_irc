/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:07:56 by yabad             #+#    #+#             */
/*   Updated: 2024/01/02 19:42:34 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICommand.hpp"

void PassCmd::execute(Context* context) const {
	(void)context;
	std::cout << "This is pass command where we should check for password." << std::endl;
}

void NickCmd::execute(Context* context) const {
	std::cout << "handling nick command." << std::endl;
	context->user->set_nickname(context->request->get_options());
}

void UserCmd::execute(Context* context) const {
	std::cout << "handling user command" << std::endl;
	context->user->set_username(context->request->get_options());
}