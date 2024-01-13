/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:45:31 by houattou          #+#    #+#             */
/*   Updated: 2024/01/09 13:14:16 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ICommand.hpp"
#include <set>
std::string WhoCmd::convert_name_channel_to_lowercase(std::string name_channel)
{
      std::string channel_name = name_channel;
        for (size_t i = 0; i < channel_name.length(); ++i) 
            channel_name[i] = std::tolower(channel_name[i]);
        return(channel_name);    
    
}

void WhoCmd::execute(Context *context)
{
    std::string name_channel = context->request->get_options();
    std::cout << "name channel is " << name_channel << std::endl;
    generate_response(context);
}
int WhoCmd::get_type()
{
    return(type);
}

// >> :Osmium.AfterNET.Org 353 non = #afet :non!yes@88ABE6.25BF1D.D03F86.88C9BD.IP @abad!yahia@88ABE6.25BF1D.D03F86.88C9BD.IP
std::string WhoCmd::get_all_users_in_channel(Context *context)
{
    std::string admin;
    std::string name_channel = convert_name_channel_to_lowercase(context->request->get_options());
    User *user = context->users->find(context->request->get_fd())->second;
    std::string members;
    members += ":myserver 353 "+ user->get_nickname() +" = " + context->request->get_options()+" :@"+ user->get_nickname()+"!"+user->get_username()+ "@"+user->get_hostname() ;
    std::map<std::string, Channel *>::iterator it = context->channels->find(name_channel);
    if(it != context->channels->end())
    {
        Channel *channel = it->second;
        std::vector<User *>users = channel->get_users();
        for(size_t i = 0; i < users.size(); i++)
        {
            if(user->get_nickname() != users[i]->get_nickname())
                members += " @"+users[i]->get_nickname()+"!"+users[i]->get_username()+ "@"+ users[i]->get_hostname() + " ";
            std::cout << users[i]->get_username() << std::endl;    
        }
       members += "\r\n";
    }
        return(members);
}


void WhoCmd::generate_response(Context*context)
{
    std::string admin;
   std::string name_channel = convert_name_channel_to_lowercase(context->request->get_options());
    std::string res;
    Request *req = context->request;
    User *user = context->users->find(context->request->get_fd())->second;
    std::map<std::string, Channel *>::iterator it = context->channels->find(name_channel);
    std::string all_users_in_channel = get_all_users_in_channel(context);
    res += all_users_in_channel;
    res += ":myserver 366 " + user->get_nickname() + " " + context->request->get_options() + ":End of NAMES list\r\n";
    res += ":myserver 324 " + user->get_nickname() + context->request->get_options() + " +\r\n";
   if(it != context->channels->end())
   {
        Channel *channel = it->second;
        std::vector<User*> users = channel->get_users();
        std::set<std::string> operators = channel->get_operators();

        for(size_t i = 0; i < users.size(); i++)
        {
            std::set<std::string>::iterator it_set = operators.find(users[i]->get_nickname());
            if(it_set != operators.end())
                admin = "H@x 0 :" + users[i]->get_realname() + "\r\n";
            else 
                admin = "Hx 0 :" + users[i]->get_realname() + "\r\n"; 
            res += ":myserver 354 " + user->get_nickname() + " 152 " +  context->request->get_options() + " "+ users[i]->get_username() + " " + users[i]->get_hostname() + " "+users[i]->get_nickname() + " " + admin;
            // res += ":myserver 352 " + user->get_nickname() + " " + req->get_options() + " " +user->get_username() + " "+ user->get_hostname() + " " + users[i]->get_nickname() + " " + admin ;
        }
     }
     //>> :Osmium.AfterNET.Org 366 hasona #gg :End of /NAMES list.
    res +=":myserver 315 " + user->get_nickname() + " " + context->request->get_options() + " :End of /WHO list." + "\r\n";
    this->response = new Response(res);
    user->add_response(this->response);

}