/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:59:51 by houattou          #+#    #+#             */
/*   Updated: 2024/01/05 18:17:22 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICommand.hpp"

void PrintCmd::execute(Context* context) const 
{
    // std::map<std::string, Channel *>::iterator it;
    // for(it = context->ch->begin(); it != context->ch->end(); it++)
    // {
    //     std::cout<<"channels are: " <<it->first <<" ";
    // }
    // std::cout<<std::endl;
    // std::cout<<"users member : -------------------" << std::endl;
    std::map<std::string, Channel*>::iterator ite = context->ch->find(context->request->get_options());
    if (ite != context->ch->end())
    {
        Channel* channel = ite->second;
        std::cout << "Users in current channel: ";
        for (std::vector<std::string>::iterator ite = channel->get_users().begin(); ite != channel->get_users().end(); ++ite)
        {
            std::cout << *ite << " ";
        }
        std::cout << std::endl;
    }
    else
        std::cout << "Channel not found." << std::endl;
}