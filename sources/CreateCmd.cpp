/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:11:41 by houattou          #+#    #+#             */
/*   Updated: 2024/01/08 12:09:31 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CreateCmd.hpp"

void CreateCmd::create_channel(Context **context)const
{
    std::string channel_name = (*context)->request->get_options();
    for (size_t i = 0; i < channel_name.length(); ++i) 
        channel_name[i] = std::tolower(channel_name[i]);
    Channel *new_channel = new Channel(channel_name);
    (*context)->channels->insert(std::make_pair(channel_name, new_channel));
}

bool CreateCmd::is_duplicate_channel_name(Context* context) const 
{
    std::string channel_name = context->request->get_options();
    for (size_t i = 0; i < channel_name.length(); ++i) 
        channel_name[i] = std::tolower(channel_name[i]);
    std::map<std::string, Channel*>::iterator it = context->channels->find(channel_name);
    if(it == context->channels->end())
        return(false);
    return(true);
}

bool CreateCmd::is_valid_channel_name(Context* context) const 
{
    if(context->request->get_options().empty())
        return(false);
    for(size_t i = 0; i < context->request->get_options().size(); i++)
    {
        if(context->request->get_options()[i] == 32 || (context->request->get_options()[i] >= 9 && \
        context->request->get_options()[i] <= 13) || \
        !isalpha(context->request->get_options()[i]))
            return(false);
    }
    return true;
}

void CreateCmd:: add_creator_to_channel(Context **context) const
{
    Request* req = (*context)->request;
    std::string name_channel = req->get_options();
    std::map<std::string, Channel *>::iterator it = (*context)->channels->find((name_channel));
    Channel *channel = it->second;
    User* user = (*context)->users->find(req->get_fd())->second;
    channel->add_user_to_channel(user->get_nickname());
}

void CreateCmd::execute(Context* context)  
{
    if(is_valid_channel_name(context) && !is_duplicate_channel_name(context))
    {
        create_channel(&context);
        add_creator_to_channel(&context);
        std::cout<<"we are create channel: " << context->request->get_options() << std::endl;
    }
    else
        std::cout<<"this channel exist" << std::endl; //should handle response
}

void CreateCmd::generate_response(Context* context) {
    (void)context;
    //generate response here
}