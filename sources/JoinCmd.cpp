/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:45:31 by houattou          #+#    #+#             */
/*   Updated: 2024/01/15 14:15:53 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCmd.hpp"

std::string JoinCmd::convert_name_channel_to_lowercase(std::string name_channel)
{
      std::string channel_name = name_channel;
        for (size_t i = 0; i < channel_name.length(); ++i) 
            channel_name[i] = std::tolower(channel_name[i]);
        return(channel_name);    
}
void JoinCmd::create_channel(Context **context)
{
    std::string channel_name = convert_name_channel_to_lowercase((*context)->request->get_options());
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
    std::string name_channel = convert_name_channel_to_lowercase(req->get_options());
    std::map<std::string, Channel *>::iterator it = (*context)->channels->find((name_channel));
    Channel *channel = it->second;
    User* user = (*context)->users->find(req->get_fd())->second;
    channel->add_user_to_channel(user);
}

std::map<std::string, Channel*> ::iterator JoinCmd::is_exist_channel(Context *context)
{
    std::string name_channel = convert_name_channel_to_lowercase(context->request->get_options());
    std::map<std::string, Channel*> *  channel  = context->channels;
    std::map<std::string, Channel *>::iterator it = channel->find(name_channel);
    if(it != channel->end())
        return(it);
    return(channel->end());    
}
void JoinCmd::execute(Context* context)
{
    if(!is_valid_channel_name(context))
        this->type = INVALID_CHANNEL_NAME;
    else
    {
        std::map<std::string, Channel *>::iterator it = is_exist_channel(context);
        if(it != context->channels->end())
        {
            Channel *channel = it->second;
            std::vector<User *> users = channel->get_users();
            User* user = context->users->find(context->request->get_fd())->second;
            if (std::find(users.begin(), users.end(), user) == users.end())
            {
                channel->add_user_to_channel(user);
                type = JOIN;
            }
        }
        else
        {
            create_channel(&context);
            add_creator_to_channel(&context);
            this->type = NEW_CHANNEL;
        }
    }
    generate_response(context);    
    
}
int JoinCmd::get_type()
{
    return(type);
}
//---------------------------------------------handle responses--------------------------------------------------------------------------------------
std::string JoinCmd::join_channel(User *user, std::string& name_channel)
{
    std::string res;
    res =":" + user->get_nickname()+ "!";
    res +=  user->get_username() + "@" +user->get_hostname();
    res += " JOIN :" + name_channel +  "\r\n";
    return(res);
}
std::string JoinCmd::no_such_channel(User *user, std::string &name_channel)
{
    std::string res;
    res = ":myserver 403 ";  
    res += user->get_nickname() + " " + name_channel;
    res += " :No such channel\r\n"; 
    return(res);
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
std::string JoinCmd:: user_status_prefix(User *user, Context *context )
{
    std::string user_status;
    if(is_operator(user,context))
        user_status = "@";
    else
        user_status= "";
    return(user_status);  
}

std::string JoinCmd::create_initial_members_string(Context *context, User *user,std::string user_status_prefix)
{
    std::string members;
    members += ":myserver 353 "+ user->get_nickname() +" = " + context->request->get_options()+ " :"+ \
    user_status_prefix + user->get_nickname() + " ";
    return(members);
}

std::string JoinCmd::append_users_to_members_string(Context *context, Channel *channel, User *user, std::string &members)
{
    std::vector<User *>users = channel->get_users();
    for(size_t i = 0; i < users.size(); i++)
    {
        if(user->get_nickname() != users[i]->get_nickname())
            members += user_status_prefix(users[i], context) + users[i]-> get_nickname() + " ";      
    }
    members += "\r\n";
    return(members);
}
std::string JoinCmd::reply_names(Context *context)
{
    User *user = context->users->find(context->request->get_fd())->second;
    std::string members = create_initial_members_string(context, user, user_status_prefix(user, context));
    std::map<std::string, Channel * > ::iterator it = is_exist_channel(context);
    if(it != context->channels->end())
    {
        Channel *channel = it->second;
        members = append_users_to_members_string(context,channel,user,members);
    }
    return(members);
}
std::string JoinCmd::reply_end_of_names(User *user, std::string &name_channel)
{
    std::string res;
     res = ":myserver 366 " + user->get_nickname();
     res += " " +name_channel;
     res += " :End of NAMES list\r\n";
     return(res);
}
std::string JoinCmd::reply_channel_mode_is(User *user, std::string& name_channel)
{
    std::string res;
    res = ":myserver 324 " + user->get_nickname() + " "+ name_channel + " +\r\n";
    return(res);
}
std::string JoinCmd::reply_topic(User *user, std::string &name_channel)
{
    std::string res;
    res = ":myserver 332 " + user->get_nickname() + " " + name_channel + " :\r\n";
    return(res); 

}
void JoinCmd::inform_operators_that_another_user_join_to_channel(User *user, Context *context, std::string &name_channel)
{
     std::string operator_res;
    std::map<std::string, Channel*>::iterator it =is_exist_channel(context);
        Channel *channel = it->second;
        std::vector<User *> users = channel->get_users();
        for(size_t i = 0; i < users.size(); i++)
        {
            if(is_operator(users[i], context))
            {
                operator_res = ":" +  user->get_nickname() + "!" ;
                operator_res +=  user->get_username() +"@"+user->get_hostname() + " JOIN" + " :" + name_channel + "\r\n";
                users[i]->add_response(new Response(operator_res));
            }
        }
    
}
void JoinCmd::generate_response(Context* context) 
{
	std::string res;
	Request* req = context->request;
    std::string name_channel = (context->request->get_options());
	User* user = context->users->find(req->get_fd())->second;
    if(get_type() == INVALID_CHANNEL_NAME)
        res = no_such_channel(user, name_channel);
    else if(get_type() == NEW_CHANNEL)
    {
        res = join_channel(user, name_channel);
        res +=reply_names(context);
        res +=reply_end_of_names(user, name_channel);
        res += reply_channel_mode_is(user, name_channel);
    }
    else if(get_type() == JOIN)
    {
        res  = join_channel(user, name_channel);
        res += reply_topic(user , name_channel);
        res +=reply_names(context);
        res +=reply_end_of_names(user, name_channel);
        res += reply_channel_mode_is(user, name_channel);
        inform_operators_that_another_user_join_to_channel(user, context, name_channel);
    }
	this->response = new Response(res);
	user->add_response(this->response);
}
