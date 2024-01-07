/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:45:31 by houattou          #+#    #+#             */
/*   Updated: 2024/01/05 18:39:50 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICommand.hpp"

void JoinCmd::execute(Context* context) const 
{
    std::string channel_name = (context)->request->get_options();
    for (size_t i = 0; i < channel_name.length(); ++i) 
        channel_name[i] = std::tolower(channel_name[i]);
    std::map<std::string, Channel *>::iterator it = context->ch->find(channel_name);
    if(it != context->ch->end())
    {
        Channel *channel = it->second;
        std::vector<std::string> users = channel->get_users();
        if (std::find(users.begin(), users.end(), context->user->get_nickname()) == users.end())
        {
            channel->add_user_to_channel(context->user->get_nickname());
            std::cout<<"[JoinCmd] " <<context->user->get_nickname() << " join to : "<< channel_name << std::endl;
        }
        else
            std::cout<<"this user is already in channel : " << channel_name << std::endl; //handle  les reponses
    
    }
}