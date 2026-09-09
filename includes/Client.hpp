/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:32:10 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/10 18:30:29 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Client
{
	private:
		int				_fd;
		std::string		_buffer;

	public:
		Client();
		~Client();

		int				getFd();
		std::string&	getBuffer();

		void	setFd(int fd);
		void	appendBuffer(const char* data, size_t len);
};
