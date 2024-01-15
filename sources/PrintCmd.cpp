// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   PrintCmd.cpp                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/01/08 16:42:39 by houattou          #+#    #+#             */
// /*   Updated: 2024/01/08 16:57:13 by houattou         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "ICommand.hpp"


// void PrintCmd::execute(Context* context)  
// {
//     (void)context;
// 	//this function just for testiong
// 	// std::cout<<"---------------channels that we are  created : ---------" << std::endl;
// 	// std::map<std::string, Channel*>::iterator it;
// 	// for(it = context->channels->begin(); it != context->channels->end(); it++)
// 	// {
// 	// 	std::cout<<"ch are :  "<<it->first  <<std::endl;
// 	// }
// 	// if(context->channels->begin() == context->channels->end())
// 	// {
// 	// 	std::cout<<"map is empty" << std::endl;
// 	// }
//     // std::map<std::string, Channel*>::iterator ite = context->channels->find(context->request->get_options());

//     // if (ite != context->channels->end())
//     // {
//     //     Channel* channel = ite->second;
//     //     std::cout << "Users in current channel: ";
//     //     for (std::vector<std::string>::iterator ite = channel->get_users().begin(); ite != channel->get_users().end(); ite++)
//     //     {
//     //         std::cout << *ite << " ";
//     //     }
//     //     std::cout << std::endl;
//     // }
//     // else
//     // {
//     //     std::cout << "Channel not found." << std::endl;
//     // }
// }

// void PrintCmd::generate_response(Context *context)  {
//     (void)context;
//     //generate response here
// }
