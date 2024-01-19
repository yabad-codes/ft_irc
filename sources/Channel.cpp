/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:02:01 by houattou          #+#    #+#             */
/*   Updated: 2024/01/19 16:15:30 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

Channel::Channel(std::string name):name_of_channel(name){}

void Channel::set_only_invite(bool _only_invite)
{
    this->only_invite = _only_invite;
}

bool Channel::get_only_invite()const
{
    return only_invite;
}

std::vector<User*> Channel::get_users() const
{
    return Users;
}

void Channel::add_user_to_channel(User *user) 
{
    if(Users.empty())
        oper.insert(user->get_nickname());
    Users.push_back(user);
}

void Channel:: make_user_operator(std::string nickname)
{
   for(std::vector<User *>::iterator it = Users.begin(); it != Users.end(); it++)
   {
    if((*it)->get_nickname() == nickname)
        oper.insert(nickname);

   }
}

void Channel::revoke_operator_status(std::string nickname)
{
    for(std::set<std::string> ::iterator it = oper.begin(); it != oper.end(); it++)
    {
        if((*it)== nickname)
        {
            oper.erase(it);
            break;
        }
    }
}
bool Channel:: is_exist_user(std::string nickename)
{
    for(size_t i = 0; i < Users.size(); i++)
    {
        if(Users[i]->get_nickname() == nickename)
            return(true);
    }
    return(false);
}
std::set<std::string> Channel::get_operators() const
{
    return(oper);
}
void Channel::kick_user(std::string nickname)
{
    for (size_t i = 0; i < Users.size(); i++)
    {
        if(Users[i]->get_nickname() == nickname)
        {
            Users.erase(Users.begin() + i);
            return;
        }
    }
}