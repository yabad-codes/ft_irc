/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:02:01 by houattou          #+#    #+#             */
/*   Updated: 2024/01/09 12:35:47 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

Channel::Channel(std::string name):name_of_channel(name){}

std::vector<User *> Channel::get_users() const
{
    return Users;
}

void Channel::add_user_to_channel(User *user) 
{
    if(Users.empty())
        oper.insert(user->get_nickname());
    Users.push_back(user);
}

void Channel:: make_user_operator(User *user)
{
   for(std::vector<User *>::iterator it = Users.begin(); it != Users.end(); it++)
   {
    if(*it == user)
        oper.insert((*it)->get_nickname());

   }
}

void Channel::revoke_operator_status(User *user)
{
    for(std::set<std::string> ::iterator it = oper.begin(); it != oper.end(); it++)
    {
        if(*it == user->get_nickname())
        {
            oper.erase(it);
            break;
        }
    }
}

std::set<std::string> Channel::get_operators() const
{
    return(oper);
}
