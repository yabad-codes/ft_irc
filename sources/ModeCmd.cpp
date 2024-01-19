/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:45:18 by houattou          #+#    #+#             */
/*   Updated: 2024/01/19 16:28:13 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeCmd.hpp"

void ModeCmd::set_channel_name(std::string _channel_name)
{
    this->channel_name = _channel_name;
}
void ModeCmd::set_option_mode(std::string _option_mode)
{
    this->option_mode = _option_mode;
}

void ModeCmd::set_nickname(std::string _nickname)
{
    this->nickname = _nickname;
}
std::string  ModeCmd::get_channel_name() const
{
    return channel_name;
}
std::string ModeCmd::get_option_mode()const
{
    return option_mode;
}
std::string ModeCmd::get_nickname() const
{
    return nickname;
}
void ModeCmd::parse_request(std::string & request)
{
    std::string channel_name;
    std::string option_mode;
    std::string nickname;
    size_t i = 0;
    for(; i < request.size() && request[i] != 32; i++)
        channel_name +=request[i];
    i++;
    for(;  i < request.size() && request[i] != 32; i++)
        option_mode += request[i];
    i++;
    for(; i < request.size() && request[i] != 32; i++)
        nickname +=request[i];
    set_channel_name(channel_name);
    set_nickname(nickname);
    set_option_mode(option_mode);    
}
bool ModeCmd::user_exist_on_that_channel(Context *context,std::string nickname, std::string channel_name)
{
    std::map<std::string, Channel *>::iterator it =context->is_exist_channel(channel_name);
    if(it != context->channels->end())
    {
        Channel *channel = it->second;
        if(channel->is_exist_user(nickname))
            return(true);
    }
    return(false);
}

bool ModeCmd::check_is_user_operator(std::string nickname, Channel *channel)
{
    std::set<std::string>operators = channel->get_operators();
    std::set<std::string>::iterator it_set = operators.find(nickname);
    if(it_set != operators.end())
        return(true);
    return(false);
}

void ModeCmd::execute(Context *context)
{
    Request *req = context->request;
    User *user = context->users->find(req->get_fd())->second;
    if (!user->is_authenticated() || !user->is_registered()) 
        generate_response(user, rpl::unregistered());
    else
    {
        std::string request = req->get_options();
        parse_request(request);
        std::string channel_name = get_channel_name();
        std::string option_mode = get_option_mode();
        std::string nickname = get_nickname();
        if(context->is_user_on_that_channel(user, channel_name))
        {
            Channel *channel = context->channels->find(channel_name)->second;
            if(context->is_operator(user, channel_name))
            {
                if(channel->is_exist_user(nickname) && user_exist_on_that_channel(context, nickname, channel_name))
                {
                    if(option_mode =="+o" && !check_is_user_operator(nickname,channel))
                    {
                        channel->make_user_operator(nickname);
                        generate_response(user, rpl::reply_make_user_operator(*user,channel_name, option_mode,nickname));
                        
                    }
                    else if(option_mode == "-o" && check_is_user_operator(nickname,channel))
                    {
                        channel->revoke_operator_status(nickname);
                        generate_response(user,rpl::reply_revoke_operator_status(*user,channel_name,option_mode,nickname));
                    }
                    else if(option_mode == "+i" && !channel->get_only_invite())
                    {
                        generate_response(user,rpl::reply_only_invite(*user,channel_name, option_mode));
                        channel->set_only_invite(true);
                    }
                    else if(option_mode == "-i" && channel->get_only_invite())
                    {
                        generate_response(user,rpl::reply_only_invite(*user,channel_name, option_mode));
                        channel->set_only_invite(false);

                    }
                    
                }

            }
            else
                generate_response(user, rpl::reply_you_are_not_channel_operator(*user,channel_name));
            

        }
        else
            generate_response(user,rpl::no_such_channel(*user, channel_name));
        
    }
}
void ModeCmd::generate_response(User *user, std::string const response)
{
      user->add_response(new Response(response));
}