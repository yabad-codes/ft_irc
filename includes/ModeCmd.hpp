/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:39:40 by houattou          #+#    #+#             */
/*   Updated: 2024/01/19 16:25:13 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ICommand.hpp"

class ModeCmd : public ICommand
{
    private:
        std::string channel_name;
        std::string option_mode;
        std::string nickname;
    public:
        void execute(Context *context);
        void generate_response(User *user, std::string const);
        void parse_request(std::string & request);
        void set_option_mode(std::string);
        void set_nickname(std::string);
        void set_channel_name(std::string);
        std::string get_channel_name()const;
        std::string get_option_mode()const;
        std::string get_nickname()const;
        bool user_exist_on_that_channel(Context *context,std::string nickname, std::string channel_name);
        bool check_is_user_operator(std::string nickname, Channel *channel);
        
};