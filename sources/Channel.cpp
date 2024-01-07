/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:02:01 by houattou          #+#    #+#             */
/*   Updated: 2024/01/05 16:48:37 by houattou         ###   ########.fr       */
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
    std::cout <<"add user to channel" << std::endl;
    Users.push_back(name_user);
}
