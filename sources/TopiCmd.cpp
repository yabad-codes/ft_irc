/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopiCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:42:42 by houattou          #+#    #+#             */
/*   Updated: 2024/01/18 18:27:19 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TopiCmd.hpp"

void TopiCmd::set_channel_name(std::string _channel_name)
{
    this->channel_name = _channel_name;
}

void TopiCmd::set_topic(std::string _topic)
{
    this->topic = _topic;
}

std::string TopiCmd::get_channel_name() const
{
    return(channel_name);
}

std::string TopiCmd::get_topic()const 
{
    return (topic);
}

void TopiCmd::parse_request(std::string &request)
{
    std::string channel_name;
    std::string topic;
        
    size_t i = 0;
    for(; request[i] != ' ' ; i++)
        channel_name += request[i]; 
    i++;
    for(; i < request.size(); i++)
        topic += request[i];
    set_channel_name(channel_name);
    set_topic(topic);   
}
std::map<std::string, Channel *> ::iterator TopiCmd::is_exist_channel(Context *context, std::string &name_channel)
{
    name_channel = context->to_lower(name_channel);
    std::map<std::string , Channel *> *channel = context->channels;
    std::map<std::string, Channel *>::iterator it = channel->find(name_channel);
    if(it != channel->end())
        return(it);
    return(channel->end());     
}
bool TopiCmd::is_user_on_that_channel(User *user, Context *context, std::string channel_name)
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
void TopiCmd::execute(Context *context)
{
    Request *req = context->request;
    User *user = context->users->find(req->get_fd())->second;
    if (!user->is_authenticated() || !user->is_registered()) 
        generate_response(user, rpl::unregistered());
    else
    {
        std::string request = req->get_options();
        parse_request(request);
        std::string topic = get_topic();
        std::string channel_name = get_channel_name();
        std::map<std::string, Channel *>::iterator it = is_exist_channel(context,channel_name);
        if(is_user_on_that_channel(user,context, channel_name))
            generate_response(user,rpl::reply_set_topic(*user,channel_name ,topic));
        else 
        {
            if(it == context->channels->end() )
                generate_response(user, rpl::no_such_channel(*user,channel_name));
            else
                generate_response(user, rpl::you_are_not_on_channel(*user, channel_name));
        }
    }
}
void TopiCmd::generate_response(User *user, std::string response)
{
    user->add_response(new Response(response));
}