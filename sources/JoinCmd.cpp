/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:45:31 by houattou          #+#    #+#             */
/*   Updated: 2024/01/08 10:17:36 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCmd.hpp"

void JoinCmd::execute(Context* context) const 
{
    std::string channel_name = (context)->request->get_options();
    for (size_t i = 0; i < channel_name.length(); ++i) 
        channel_name[i] = std::tolower(channel_name[i]);
    std::map<std::string, Channel *>::iterator it = context->channels->find(channel_name);
    if(it != context->channels->end())
    {
        Channel *channel = it->second;
        std::vector<std::string> users = channel->get_users();
        User* user = context->users->find(context->request->get_fd())->second;
        if (std::find(users.begin(), users.end(), user->get_nickname()) == users.end())
        {
            channel->add_user_to_channel(user->get_nickname());
            std::cout<<"[JoinCmd] " << user->get_nickname() << " join to : " << channel_name << std::endl;
        }
        else
            std::cout<<"this user is already in channel : " << channel_name << std::endl; //handle  les reponses
    
    }
}

void JoinCmd::generate_response() const {
    //generate response here
}