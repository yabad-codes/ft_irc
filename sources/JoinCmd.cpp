/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:45:31 by houattou          #+#    #+#             */
/*   Updated: 2024/01/09 13:14:16 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCmd.hpp"

void JoinCmd::create_channel(Context **context)
{
    std::string channel_name = (*context)->request->get_options();
    for (size_t i = 0; i < channel_name.length(); ++i) 
        channel_name[i] = std::tolower(channel_name[i]);
    Channel *new_channel = new Channel(channel_name);
    (*context)->channels->insert(std::make_pair(channel_name, new_channel));
}

bool JoinCmd::is_duplicate_channel_name(Context* context)
{
    std::string channel_name = context->request->get_options();
    for (size_t i = 0; i < channel_name.length(); ++i) 
        channel_name[i] = std::tolower(channel_name[i]);
    std::map<std::string, Channel*>::iterator it = context->channels->find(channel_name);
    if(it == context->channels->end())
        return(false);
    return(true);
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
    std::string name_channel = req->get_options();
    std::map<std::string, Channel *>::iterator it = (*context)->channels->find((name_channel));
    Channel *channel = it->second;
    User* user = (*context)->users->find(req->get_fd())->second;
    channel->add_user_to_channel(user->get_nickname());
}

std::string JoinCmd::convert_name_channel_to_lowercase(std::string name_channel)
{
      std::string channel_name = name_channel;
        for (size_t i = 0; i < channel_name.length(); ++i) 
            channel_name[i] = std::tolower(channel_name[i]);
        return(channel_name);    
    
}
void JoinCmd::execute(Context* context)
{
    std::string channel_name = convert_name_channel_to_lowercase((context)->request->get_options());
    if(!is_valid_channel_name(context))
    {
        this->type = INV;
        generate_response(context);
        return;
    }
    else
    {
        std::map<std::string, Channel *>::iterator it = context->channels->find(channel_name);
        if(it != context->channels->end())
        {
            Channel *channel = it->second;
            std::vector<std::string> users = channel->get_users();
            User* user = context->users->find(context->request->get_fd())->second;
            if (std::find(users.begin(), users.end(), user->get_nickname()) == users.end())
            {
                channel->add_user_to_channel(user->get_nickname());
                // std::string reponse = "@localost" + " 354 " + user->get_nickname() +" " + channel_name + 
                std::cout<<"[JoinCmd] " << user->get_nickname() << " join to : " << channel_name << std::endl;
            }
            else
                std::cout<<"generete a reponse" << std::endl;
        }
        else
            {
                create_channel(&context);
                add_creator_to_channel(&context);
                this->type = NEW;
                generate_response(context);
                
            }
    }
    
}
int JoinCmd::get_type()
{
    return(type);
}

void JoinCmd::generate_response(Context* context) 
{
	std::string res;
	Request* req = context->request;
    std::string name_channel = convert_name_channel_to_lowercase(context->request->get_options());
	User* user = context->users->find(req->get_fd())->second;
    if(get_type() == INV)
        res = ":@localhost 403"  + user->get_nickname() + " " + context->request->get_options() + " " +":No such channel " + "\r\n";
    else if(get_type() == NEW)
        res = ":" + user->get_nickname()+ "!"+user->get_username()+ "@localhost" + " " + "JOIN"+ " "+ ":"+req->get_options()+"\r\n";
	this->response = new Response(res);
	user->add_response(this->response);
}

