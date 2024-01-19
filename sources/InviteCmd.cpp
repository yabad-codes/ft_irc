/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:50:42 by houattou          #+#    #+#             */
/*   Updated: 2024/01/17 19:49:12 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteCmd.hpp"


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
bool InviteCmd::is_exist_user(std::string nickname, Context *context)
{
    std::unordered_map<int , User*> ::iterator it;
    for(it = context->users->begin(); it != context->users->end(); it++)
    {
        if((it)->second->get_nickname() == nickname)
            return(true);
    }
    return(false);
}
std::map<std::string, Channel *> ::iterator InviteCmd::is_exist_channel(Context *context, std::string &name_channel)
{
    name_channel = context->to_lower(name_channel);
    std::map<std::string , Channel *> *channel = context->channels;
    std::map<std::string, Channel *>::iterator it = channel->find(name_channel);
    if(it != channel->end())
        return(it);
    return(channel->end());     
}
bool InviteCmd::is_user_on_that_channel(User *user, Context *context, std::string channel_name)
{
    std::map<std::string, Channel *>::iterator it = is_exist_channel(context, channel_name);
    if(it != context->channels->end())
    {
        Channel *channel = it->second;
        if(channel->is_exist_user(user->get_nickname()))
            return(true);
    }
    return(false);
}

User * InviteCmd::found_user(std::string nickname, Context *context)
{
    std::unordered_map<int , User*> ::iterator it;
    for(it = context->users->begin(); it != context->users->end(); it++)
    {
        if((it)->second->get_nickname() == nickname)
            return(it->second);
    }
    return(NULL);
}

void InviteCmd::invite_user(User *user,std::string nickname, std::string channel_name, Context *context)
{
     User *user_invite = found_user(nickname, context);
     if(user_invite != NULL)
        generate_response(user_invite, rpl::reply_invite_user(*user, nickname, channel_name));
}

void InviteCmd::execute(Context* context)
{
    Request *req = context->request; 
    std::string request = req->get_options();
    User *user = context->users->find(req->get_fd())->second;
    if (!user->is_authenticated() || !user->is_registered()) 
        generate_response(user, rpl::unregistered());
    else 
    {
        parse_request(request);
        std::string nickname_of_user_invite = get_nickname();
        std::string channel_name = get_channel_name();
        std::map<std::string, Channel *>::iterator it = is_exist_channel(context, channel_name);
        if(is_exist_user(nickname_of_user_invite,context) && it != context->channels->end() \
        && !is_user_on_that_channel(user, context, channel_name))
            generate_response(user, rpl::you_are_not_on_channel(*user, channel_name));
        else if(is_exist_user(nickname_of_user_invite, context)) 
        {
            generate_response(user, rpl::reply_exist_user_and_channel(*user, nickname_of_user_invite, channel_name));
            invite_user(user, nickname_of_user_invite, channel_name, context);
        }
        else 
            generate_response(user, rpl::no_such_nick(*user, nickname_of_user_invite));   
    }
}

void InviteCmd::generate_response(User *user, std::string const response)
{
    user->add_response(new Response(response));
}