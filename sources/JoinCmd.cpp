/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:45:31 by houattou          #+#    #+#             */
/*   Updated: 2024/01/18 21:43:01 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCmd.hpp"

std::string JoinCmd::to_lower(std::string name_channel)
{
      std::string channel_name = name_channel;
        for (size_t i = 0; i < channel_name.length(); ++i) 
            channel_name[i] = std::tolower(channel_name[i]);
        return(channel_name);    
}
void JoinCmd::create_channel(Context **context, std::string channel_name)
{
    std::string channel = to_lower(channel_name);
    Channel *new_channel = new Channel(channel);
    (*context)->channels->insert(std::make_pair(channel, new_channel));
}

bool JoinCmd::is_valid_channel_name(std::string channel_name)
{
    if(channel_name.empty()||channel_name[0] != '#')
        return(false);
    for(size_t i = 1; i < channel_name.size(); i++)
    {
        if(channel_name[i] == 32 || (channel_name[i] >= 9 && \
        channel_name[i] <= 13))
            return(false);
    }
    return true;
}

void JoinCmd:: add_creator_to_channel(Context **context, std::string channel_name) 
{
    Request* req = (*context)->request;
    std::string name_channel = to_lower(channel_name);
    std::map<std::string, Channel *>::iterator it = (*context)->channels->find((channel_name));
    Channel *channel = it->second;
    User* user = (*context)->users->find(req->get_fd())->second;
    channel->add_user_to_channel(user);
}

std::map<std::string, Channel*> ::iterator JoinCmd::is_exist_channel(Context *context, std::string& channel_name)
{
    std::string name_channel = to_lower(channel_name);
    std::map<std::string, Channel*> *  channel  = context->channels;
    std::map<std::string, Channel *>::iterator it = channel->find(name_channel);
    if(it != channel->end())
        return(it);
    return(channel->end());    
}

bool JoinCmd::is_operator(User *user, Context *context, std::string channel_name)
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
const char* JoinCmd::user_status_prefix(User *user, Context *context, std::string channel_name)
{
    if (is_operator(user,context, channel_name))
        return "@";
    return "";
}

std::string JoinCmd::get_members_string(Context *context, Channel *channel, User *user, std::string channel_name)
{
    std::string members;
    std::vector<User *>users = channel->get_users();
    for(size_t i = 0; i < users.size(); i++)
    {
        if(user->get_nickname() != users[i]->get_nickname())
            members += user_status_prefix(users[i], context, channel_name) + users[i]-> get_nickname() + " ";
    }
    return(members);
}

void JoinCmd::inform_operators_that_another_user_join_to_channel(User *user, Context *context, std::string &channel_name)
{
    std::string operator_res;
    std::map<std::string, Channel*>::iterator it = is_exist_channel(context, channel_name);
    Channel *channel = it->second;
    std::vector<User *> users = channel->get_users();
    for(size_t i = 0; i < users.size(); i++)
    {
        if(is_operator(users[i], context,channel_name))
        {
            std::string operator_res = rpl::join_channel(*user, channel_name);
            generate_response(users[i],operator_res);
        }
    }
}
void JoinCmd::set_channel_name(std::string _channel_name)
{
    this->channel_name = _channel_name;
}
std::string JoinCmd::get_channel_name() const
{
    return channel_name;
}
void JoinCmd::parse_request(std::string request)
{
    std::string channel_name;
    for(size_t i = 0; i < request.size() && request[i] != ' '; i++)
        channel_name += request[i];
    set_channel_name(channel_name); 
}
void JoinCmd::execute(Context* context)
{
    Request* req = context->request;
    User* user = context->users->find(req->get_fd())->second;
    
    if (!user->is_authenticated() || !user->is_registered()) 
        generate_response(user, rpl::unregistered());
    else
    {
        parse_request(context->request->get_options());
        std::string channel_name = get_channel_name();
        if (!is_valid_channel_name(channel_name))
            generate_response(user, rpl::no_such_channel(*user, channel_name));
        else
        {
            std::map<std::string, Channel *>::iterator it = is_exist_channel(context, channel_name);
            if(it != context->channels->end())
            {
                Channel *channel = it->second;
                std::vector<User *> users = channel->get_users();
                if (std::find(users.begin(), users.end(), user) == users.end())
                {
                    channel->add_user_to_channel(user);
                    generate_response(user, rpl::join_channel(*user, channel_name));
                    generate_response(user, rpl::reply_topic(*user, channel_name));
                    generate_response(user, rpl::reply_names(*user, channel_name, user_status_prefix(user, context, channel_name), get_members_string(context, channel, user, channel_name)));
                    generate_response(user, rpl::reply_end_of_names(*user, channel_name));
                    generate_response(user, rpl::reply_channel_mode_is(*user, channel_name));
                    inform_operators_that_another_user_join_to_channel(user, context, channel_name);
                }
            }
            else
            {
                create_channel(&context, channel_name);
                add_creator_to_channel(&context, channel_name);
                it = is_exist_channel(context, channel_name);
                generate_response(user, rpl::join_channel(*user, channel_name));
                generate_response(user, rpl::reply_names(*user, channel_name, user_status_prefix(user, context, channel_name), get_members_string(context, it->second, user, channel_name)));
                generate_response(user, rpl::reply_end_of_names(*user, channel_name));
                generate_response(user, rpl::reply_channel_mode_is(*user, channel_name));
            }
        }
    }
}

void JoinCmd::generate_response(User* user, std::string const response) 
{
	user->add_response(new Response(response));
}
