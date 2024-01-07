/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:28:47 by yabad             #+#    #+#             */
/*   Updated: 2024/01/07 15:49:57 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <iostream>

class Response {
	private:
		std::string response;
	public:
		Response(std::string res);
		~Response();
		const char* get_response() const;
		size_t get_size() const;
};

#endif