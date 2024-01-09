/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:00:10 by houattou          #+#    #+#             */
/*   Updated: 2024/01/09 12:33:57 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "User.hpp"
#include "Request.hpp"
#include<set>
class Channel 
{
    private:
      std::string name_of_channel;
      std::vector<std::string> Users;
      std::set<std::string>oper;
    public:
      Channel(std::string);
      void add_user_to_channel(std::string);
      std::vector<std::string> get_users() const;
      void make_user_operator(std::string & nickname);
      void revoke_operator_status(std::string & nickname);
      // void remove_user(User *user);
      // void send_message(const std::string &message, const User &sender)const;
        
};
