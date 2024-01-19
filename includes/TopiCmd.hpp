/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopiCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:16:34 by houattou          #+#    #+#             */
/*   Updated: 2024/01/18 12:54:01 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICommand.hpp"

class TopiCmd : public ICommand
{
    private:
        std::string channel_name;
        std::string topic;
    public :
        void execute(Context*);
		void generate_response(User*, std::string const);
        void parse_request(std::string &);
        void set_channel_name(std::string);
        void set_topic(std::string);
        std::string get_channel_name()const;
        std::string get_topic()const;
        bool is_user_on_that_channel(User *user, Context *context, std::string channel_name);
        std::map<std::string, Channel *> ::iterator is_exist_channel(Context *context, std::string &name_channel);

};