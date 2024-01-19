/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:26:01 by houattou          #+#    #+#             */
/*   Updated: 2024/01/17 12:43:03 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ICommand.hpp"

class InviteCmd : public ICommand
{
    private:
        std::string channel_name;
        std::string nickname;
    public:
        void execute(Context*);
        void generate_response(User*, std::string const);
        void set_channelname(std::string);
        void set_nickname(std::string nickname);
        std::string get_channel_name();
        std::string get_nickname();
        void parse_request(std::string &request);
        bool is_exist_user(std::string , Context  *);
        bool is_user_on_that_channel(User *, Context *, std::string );
        std::map<std::string, Channel *> ::iterator is_exist_channel(Context *context, std::string&);
        void invite_user(User *,std::string nickname, std::string channel_name, Context *context);
        User * found_user(std::string nickname, Context *context);
};
