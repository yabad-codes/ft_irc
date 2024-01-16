/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:00:53 by houattou          #+#    #+#             */
/*   Updated: 2024/01/16 19:43:16 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"KickCmd.hpp"

void KickCmd::set_channelname(std::string name_ch)
{
    this->channel_name = name_ch;
}
void KickCmd::set_username(std::string nickname)
{
    this->user_name = nickname;
}
std::string KickCmd::get_channel_name()
{
    return channel_name;
}
std::string KickCmd::get_username()
{
    return user_name;
}
void KickCmd::parse_channel_and_user(std::string &request)
{
    std::string channel_name;
    std::string user_name;
        
    size_t i = 0;
    for(; request[i] != ' ' ; i++)
        channel_name += request[i]; 
    i++;
    for(; i < request.size(); i++)
        user_name += request[i];
    set_channelname(channel_name);
    set_username(user_name);       
}

std::map<std::string, Channel *> ::iterator KickCmd::is_exist_channel(Context *context, std::string &name_channel)
{
    name_channel = context->to_lower(name_channel);
    std::map<std::string , Channel *> *channel = context->channels;
    std::map<std::string, Channel *>::iterator it = channel->find(name_channel);
    if(it != channel->end())
        return(it);
    return(channel->end());     
}

bool KickCmd::is_operator(User *user, Context *context, std::string channel_name)
{
    std::map<std::string, Channel *> ::iterator it =is_exist_channel(context, channel_name);
    if(it != context->channels->end())
    {
        Channel *channel = it->second;
        std::set<std::string>operators = channel->get_operators();
        std::set<std::string>::iterator it_set = operators.find(user->get_nickname());
        if(it_set != operators.end())
            return(true);
    }
    return(false);
}

void KickCmd::handle_response_for_kick_user(User* user, std::string user_kicked, std::string channel_name, Channel *channel)
{
    std::string response;
    std::vector<User *> users = channel->get_users();
    for(size_t i = 0; i < users.size(); i++)
        generate_response(users[i],rpl::reply_kick_user(*user, user_kicked, channel_name));
}

void KickCmd::execute(Context* context) 
{
    std::string channel_name;
    std::string user_kicked;
    std::string parse = context->request->get_options();
    User *user = context->users->find(context->request->get_fd())->second;
    if (!user->is_authenticated() || !user->is_registered()) {
        generate_response(user, rpl::unregistered());
        return ;
    }
    parse_channel_and_user(parse);
    channel_name = get_channel_name();
    user_kicked = get_username();
    std::map<std::string, Channel *>::iterator it = is_exist_channel(context,channel_name);
    if(it != context->channels->end())
    {
        if(is_operator(user,context ,channel_name))
        {
            Channel *channel = it->second;
            if(channel->is_exist_user(user_kicked))
            {
                handle_response_for_kick_user(user, user_kicked, channel_name, channel);
                channel->kick_user(user_kicked);
            }
            else
                generate_response(user, rpl::reply_are_not_on_channel(*user, user_kicked, channel_name));
        }
        else
            generate_response(user, rpl::reply_you_are_not_channel_operator(*user, channel_name));
    }
    else
        generate_response(user, rpl::no_such_channel(*user, channel_name));
}

void KickCmd::generate_response(User* user, std::string const response) 
{
    user->add_response(new Response(response));
}
