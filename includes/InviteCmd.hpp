/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:26:01 by houattou          #+#    #+#             */
/*   Updated: 2024/01/17 11:00:54 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ICommand.hpp"

class InviteCmd : public ICommand
{
    private:
        std::string channel_name;
        std::sring nickname;
    public:
        void execute(Context*);
        void generate_response(User*, std::string const);
        void set_channelname(std::string);
        void set_nickname(std::string nickname);
        std::string get_channel_name();
        std::string get_nickname();
        void parse_request(std::string &request);
};
