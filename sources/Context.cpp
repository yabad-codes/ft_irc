/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:19:05 by houattou          #+#    #+#             */
/*   Updated: 2024/01/16 18:03:19 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ICommand.hpp"

std::string Context::to_lower(std::string name_channel)
{
    std::string channel_name = name_channel;
    for (size_t i = 0; i < channel_name.length(); ++i) 
        channel_name[i] = std::tolower(channel_name[i]);
    return(channel_name);    
}