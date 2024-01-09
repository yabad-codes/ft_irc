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

Channel::Channel(std::string name):name_of_channel(name)
{
   
}
std::vector<std::string> Channel::get_users() const
{
    return Users;
}
void Channel::add_user_to_channel(std::string name_user) 
{
    if(Users.empty())
        oper.insert(name_user);
    Users.push_back(name_user);
}
void Channel:: make_user_operator(std::string & nickname)
{
    if(std::find(Users.begin(), Users.end(), nickname) != Users.end())
    {
        oper.insert(nickname);
    }
}
void Channel::revoke_operator_status(std::string &nickname)
{
    if(std::find(oper.begin(), oper.end(), nickname) != oper.end())
        oper.erase(nickname);
}
