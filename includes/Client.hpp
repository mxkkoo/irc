/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:32:10 by kyoussou          #+#    #+#             */
/*   Updated: 2026/09/10 18:53:13 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Client
{
	private:
		int				_fd;
		std::string		_buffer;

		std::string		_username;
		std::string		_realname;
		std::string		_nickname;
		bool			_password;

	public:
		Client();
		~Client();

		int				getFd();
		std::string&	getBuffer();
		std::string&	getNickname();
		std::string&	getUsername();

		void	setFd(int fd);
		void	setNickname(std::string nickname);
		void	setUsername(std::string username, std::string realname);
		void	setPassword(bool password);

		bool	hasNickname();
		bool	hasUsername();
		bool	isRegistered();

		void	appendBuffer(const char* data, size_t len);
};
