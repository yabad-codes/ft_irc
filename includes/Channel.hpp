/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:00:10 by houattou          #+#    #+#             */
/*   Updated: 2024/01/05 18:47:43 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "User.hpp"
#include "Request.hpp"
class Channel 
{
    private:
      std::string name_of_channel;
      std::vector<std::string> Users;
    public:
      Channel(std::string);
      void add_user_to_channel(std::string);
      std::vector<std::string> get_users() const;
      // void remove_user(User *user);
      // void send_message(const std::string &message, const User &sender)const;
        
};
