/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:45:31 by houattou          #+#    #+#             */
/*   Updated: 2024/01/15 17:29:03 by yabad            ###   ########.fr       */
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
void JoinCmd::create_channel(Context **context)
{
    std::string channel_name = to_lower((*context)->request->get_options());
    Channel *new_channel = new Channel(channel_name);
    (*context)->channels->insert(std::make_pair(channel_name, new_channel));
}

bool JoinCmd::is_valid_channel_name(Context* context)
{
    if(context->request->get_options().empty()|| context->request->get_options()[0] != '#')
        return(false);
    for(size_t i = 1; i < context->request->get_options().size(); i++)
    {
        if(context->request->get_options()[i] == 32 || (context->request->get_options()[i] >= 9 && \
        context->request->get_options()[i] <= 13) || \
        !isalpha(context->request->get_options()[i]))
            return(false);
    }
    return true;
}

void JoinCmd:: add_creator_to_channel(Context **context) 
{
    Request* req = (*context)->request;
    std::string name_channel = to_lower(req->get_options());
    std::map<std::string, Channel *>::iterator it = (*context)->channels->find((name_channel));
    Channel *channel = it->second;
    User* user = (*context)->users->find(req->get_fd())->second;
    channel->add_user_to_channel(user);
}

std::map<std::string, Channel*> ::iterator JoinCmd::is_exist_channel(Context *context)
{
    std::string name_channel = to_lower(context->request->get_options());
    std::map<std::string, Channel*> *  channel  = context->channels;
    std::map<std::string, Channel *>::iterator it = channel->find(name_channel);
    if(it != channel->end())
        return(it);
    return(channel->end());    
}
void JoinCmd::execute(Context* context)
{
    Request* req = context->request;
    User* user = context->users->find(req->get_fd())->second;
    std::string channel_name = req->get_options();

    if (!user->is_authenticated() || !user->is_registered()) {
        generate_response(user, rpl::unregistered());
        return ;
    }
    if (!is_valid_channel_name(context))
        generate_response(user, rpl::no_such_channel(*user, channel_name));
    else
    {
        std::map<std::string, Channel *>::iterator it = is_exist_channel(context);
        if(it != context->channels->end())
        {
            Channel *channel = it->second;
            std::vector<User *> users = channel->get_users();
            if (std::find(users.begin(), users.end(), user) == users.end())
            {
                channel->add_user_to_channel(user);
                generate_response(user, rpl::join_channel(*user, channel_name));
                generate_response(user, rpl::reply_topic(*user, channel_name, std::string("TOPIC NEED TO BE ADDED LATER")));
                generate_response(user, rpl::reply_names(*user, channel_name, user_status_prefix(user, context), get_members_string(context, channel, user)));
                generate_response(user, rpl::reply_end_of_names(*user, channel_name));
                generate_response(user, rpl::reply_channel_mode_is(*user, channel_name));
                inform_operators_that_another_user_join_to_channel(user, context, channel_name);
            }
        }
        else
        {
            create_channel(&context);
            add_creator_to_channel(&context);
            it = is_exist_channel(context);
            generate_response(user, rpl::join_channel(*user, channel_name));
            generate_response(user, rpl::reply_names(*user, channel_name, user_status_prefix(user, context), get_members_string(context, it->second, user)));
            generate_response(user, rpl::reply_end_of_names(*user, channel_name));
            generate_response(user, rpl::reply_channel_mode_is(*user, channel_name));
        }
    }
}

bool JoinCmd::is_operator(User *user, Context *context)
{
    std::map<std::string, Channel *> ::iterator it =is_exist_channel(context);
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
const char* JoinCmd::user_status_prefix(User *user, Context *context)
{
    if (is_operator(user,context))
        return "@";
    return "";
}

std::string JoinCmd::get_members_string(Context *context, Channel *channel, User *user)
{
    std::string members;
    std::vector<User *>users = channel->get_users();
    for(size_t i = 0; i < users.size(); i++)
    {
        if(user->get_nickname() != users[i]->get_nickname())
            members += user_status_prefix(users[i], context) + users[i]-> get_nickname() + " ";
    }
    return(members);
}

void JoinCmd::inform_operators_that_another_user_join_to_channel(User *user, Context *context, std::string &name_channel)
{
    std::string operator_res;
    std::map<std::string, Channel*>::iterator it = is_exist_channel(context);
    Channel *channel = it->second;
    std::vector<User *> users = channel->get_users();
    for(size_t i = 0; i < users.size(); i++)
    {
        if(is_operator(users[i], context))
        {
            std::string operator_res = rpl::join_channel(*user, name_channel);
            users[i]->add_response(new Response(operator_res));
        }
    }
}
void JoinCmd::generate_response(User* user, std::string const response) 
{
	user->add_response(new Response(response));
}
