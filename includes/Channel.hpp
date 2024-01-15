/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:00:10 by houattou          #+#    #+#             */
/*   Updated: 2024/01/12 11:31:42 by houattou         ###   ########.fr       */
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
      std::vector<User *> Users;
      std::set<std::string>oper;
    public:
      Channel(std::string);
      void add_user_to_channel(User *);
      std::vector<User *> get_users() const;
      void make_user_operator(User *);
      void revoke_operator_status(User *user);
      std::set<std::string> get_operators() const;
      // void remove_user(User *user);
      // void send_message(const std::string &message, const User &sender)const;
        
};

