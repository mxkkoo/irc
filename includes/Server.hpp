/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:10:08 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/10 18:22:57 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <poll.h>
#include <vector>
#include <map>

#include "Client.hpp"

class Server
{
	private:
		int							_port;
		std::string					_password;

		int							_listenSocket;
		std::map<int, Client>		_clients;
		std::vector<struct pollfd>	_pollFds;

		static bool					_signal;

	public:
		Server(char* av[]);
		~Server();

		int			getPort() const;
		std::string	getPassword() const;
		
		static void	handleSignal(int signum);

		void		start();
		void		mainLoop();
		void		newClient();
		void		removeClient(int fd);
		void		receiveData(struct pollfd pollFd);

		void		setupSocket();
		void		addFd(int fd);
		void		closeSocket();
		Client&		getClientByFd(int fd);
};
