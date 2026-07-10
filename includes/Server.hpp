/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:10:08 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/10 16:50:56 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <poll.h>
#include <vector>

class Server
{
	private:
		static bool					signal;

		int							_port;
		std::string					_password;
		std::vector<struct pollfd>	_fds;
		int							_listenSocket;

	public:
		Server(char* av[]);
		~Server();

		int			getPort() const;
		std::string	getPassword() const;
		
		void		handleSignal(int signum);
		void		setupSocket();
		void		start();
};
