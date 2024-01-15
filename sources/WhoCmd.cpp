// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   WhoCmd.cpp                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/01/05 17:45:31 by houattou          #+#    #+#             */
// /*   Updated: 2024/01/09 13:14:16 by houattou         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// # include "ICommand.hpp"
// #include <set>

// std::string convert_name_channel_to_lowercase(std::string name_channel);
// class WhoCmd : public ICommand 
// {
// 	private:
//         response_type type;
// 		bool is_operator(User *user,Context *context);
//         int get_type();

// 		std::string  user_status_prefix(User *user, Context *context);

// 		std::string append_users_to_members_string(Context *context, Channel *channel, User *user, std::string members);
// 		std::string create_initial_members_string(Context *context, User *user,std::string user_status_prefix);
// 		std::string create_members_string(Context *context, User *user, std::string admin);
// 		std::string reply_names(Context *);
// 		// std::string get_users_in_channel(Context *context, std::string name_channel, std::string members, User *user, std::string admin);
// 		std::map<std::string, Channel*> ::iterator is_exist_channel(Context *context);
// 		std::string reply_end_of_names(User *user, std::string name_channel);
// 		std::string reply_channel_mode_is(User *user, std::string name_channel);
// 		Response* response;
// 	public:
// 		void execute(Context*);
// 		void generate_response(Context*);
// };
// std::string convert_name_channel_to_lowercase(std::string name_channel)
// {
//       std::string channel_name = name_channel;
//         for (size_t i = 0; i < channel_name.length(); ++i) 
//             channel_name[i] = std::tolower(channel_name[i]);
//         return(channel_name);
// }

// int WhoCmd::get_type()
// {
//     return(type);
// }
// std::map<std::string, Channel*> ::iterator WhoCmd::is_exist_channel(Context *context)
// {
//     std::string name_channel = convert_name_channel_to_lowercase(context->request->get_options());
//     std::map<std::string, Channel*> *  channel  = context->channels;
//     std::map<std::string, Channel *>::iterator it = channel->find(name_channel);
//     if(it != channel->end())
//         return(it);
//     return(channel->end());    
// }

// bool WhoCmd::is_operator(User *user, Context *context)
// {
//     std::map<std::string, Channel *> ::iterator it =is_exist_channel(context);
//     if(it != context->channels->end())
//     {
//         Channel *channel = it->second;
//         std::set<std::string>operators = channel->get_operators();
//         std::set<std::string>::iterator it_set = operators.find(user->get_nickname());
//         if(it_set != operators.end())
//             return(true);
//     }
//     return(false);
// }
// std::string WhoCmd:: user_status_prefix(User *user, Context *context )
// {
//     std::string user_status;
//     if(is_operator(user,context))
//         user_status = "@";
//     else
//         user_status= "";
//     return(user_status);  

// }
// std::string WhoCmd::create_initial_members_string(Context *context, User *user,std::string user_status_prefix)
// {
//     std::string members;
//     members += ":myserver 353 "+ user->get_nickname() +" = " + context->request->get_options()+ " :"+ \
//     user_status_prefix + user->get_nickname() + " ";
//     return(members);
// }

// std::string WhoCmd::append_users_to_members_string(Context *context, Channel *channel, User *user, std::string members)
// {
//     std::vector<User *>users = channel->get_users();
//     for(size_t i = 0; i < users.size(); i++)
//     {
//         if(user->get_nickname() != users[i]->get_nickname())
//             members += user_status_prefix(users[i], context) + users[i]-> get_nickname() + " ";      
//     }
//     members += "\r\n";
//     return(members);
// }
// std::string WhoCmd::reply_names(Context *context)
// {
//     User *user = context->users->find(context->request->get_fd())->second;
//     std::string members = create_initial_members_string(context, user, user_status_prefix(user, context));
//     std::map<std::string, Channel * > ::iterator it = is_exist_channel(context);
//     if(it != context->channels->end())
//     {
//         Channel *channel = it->second;
//         members = append_users_to_members_string(context,channel,user,members);
//     }
//     return(members);
// }

// void WhoCmd::execute(Context *context)
// {
//     generate_response(context);
// }

// std::string WhoCmd::reply_end_of_names(User *user, std::string name_channel)
// {
//     std::string res;
//      res = ":myserver 366 " + user->get_nickname();
//      res += " " +name_channel;
//      res += ":End of NAMES list\r\n";
//      return(res);
// }
// std::string WhoCmd::reply_channel_mode_is(User *user, std::string name_channel)
// {
//     std::string res;
//     res = ":myserver 324 " + user->get_nickname() + " "+ name_channel + " +\r\n";
//     return(res);
// }
// void WhoCmd::generate_response(Context*context)
// {
//     (void)context;
  
//     // std::string admin;
// //    std::string name_channel = (context->request->get_options());
// //     std::string res;
// //     Request *req = context->request;
// //     User *user = context->users->find(context->request->get_fd())->second;
// //     // std::map<std::string, Channel *>::iterator it = context->channels->find(name_channel);
// //     res = reply_names(context);
// //     // res += all_users_in_channel;
// //     res += reply_end_of_names(user,name_channel);
// //     res += reply_channel_mode_is(user, name_channel);
// //     this->response = new Response(res);
// //     user->add_response(this->response);
// //    if(it != context->channels->end())
// //    {
// //         Channel *channel = it->second;
// //         std::vector<User*> users = channel->get_users();
// //         std::set<std::string> operators = channel->get_operators();

// //         for(size_t i = 0; i < users.size(); i++)
// //         {
// //             std::set<std::string>::iterator it_set = operators.find(users[i]->get_nickname());
// //             if(it_set != operators.end())
// //                 admin = "H@x 0 :" + users[i]->get_realname() + "\r\n";
// //             else 
// //                 admin = "Hx 0 :" + users[i]->get_realname() + "\r\n"; 
// //             res += ":myserver 354 " + user->get_nickname() + " 152 " +  context->request->get_options() + " "+ users[i]->get_username() + " " + users[i]->get_hostname() + " "+users[i]->get_nickname() + " " + admin;
// //         }
// //      }
// //     res +=":myserver 315 " + user->get_nickname() + " " + context->request->get_options() + " :End of /WHO list." + "\r\n";
// }