/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:50:42 by houattou          #+#    #+#             */
/*   Updated: 2024/01/17 11:12:14 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteCmd.hpp"
// >> :ircserv.42.fr 443 yaya hassna #random :is already on channel
//     // >> :yaya!ouattou@localhost 341 hassna yaya #random

void InviteCmd::set_channelname(std::string name_ch)
{
    this->channel_name = name_ch;
}
void InviteCmd::set_nickname(std::string nickname)
{
    this->nickname = nickname;
}
std::string InviteCmd::get_channel_name()
{
    return channel_name;
}
std::string InviteCmd::get_nickname()
{
    return nickname;
}
void InviteCmd::parse_request(std::string &request)
{
    std::string channel_name;
    std::string nickname;
        
    size_t i = 0;
    for(; request[i] != ' ' ; i++)
        nickname += request[i]; 
    i++;
    for(; i < request.size(); i++)
        channel_name += request[i];
    set_channelname(channel_name);
    set_nickname(nickname);       
}
void InviteCmd::execute(Context* context)
{
    Request *req = context->request; 
    std::string request = req->get_options();
    User *user = context->users->find(req->get_fd())->second;
    if (!user->is_authenticated() || !user->is_registered()) 
    {
        generate_response(user, rpl::unregistered());
        return ;
    }
    parse_request(request);
    std::string nickname_of_user_invite = get_nickname();
    std::string channel_name = get_channel_name();
    std::cout <<"nickname " << nickname_of_user_invite << std::endl;
    std::cout <<"channel name is : " << channel_name << std::endl;
    if(is_exist_user)

    
}

void InviteCmd::generate_response(User *user, std::string const response)
{
    (void)user;
    (void)response;
}