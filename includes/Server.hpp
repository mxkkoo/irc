/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:10:08 by kyoussou          #+#    #+#             */
/*   Updated: 2026/09/15 17:02:26 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Channel.hpp"
#include <vector>
#include <map>
#include <poll.h>

class Server {
//Server class: Everything needed to run and use the server

	private:
		int							_port;
		std::string					_password;

		int								_listenSocket;
		std::map<int, Client>			_clients;
		std::map<std::string, Channel>	_channels;
		std::vector<struct pollfd>		_pollFds;

		static bool					_signal;

	public:
		Server(char* av[]);
		~Server();

		static void	handleSignal(int signum);

		void		start();
		void		mainLoop();

		void		newClient();
		void		removeClient(int fd);
		void		receiveData(struct pollfd pollFd);

		void		processBuffer(Client& client);
		void		processLine(Client& client, std::string& line);
		void		dispatch(Client& client, std::string command, std::vector<std::string> args);

		void		handleCap(Client& client, std::vector<std::string>& args);
		void		handlePing(Client& client, std::vector<std::string>& args);

		void		commandPass(Client& client, std::vector<std::string>& args);
		void		commandNick(Client& client, std::vector<std::string>& args);
		void		commandUser(Client& client, std::vector<std::string>& args);
		void		commandJoin(Client& client, std::vector<std::string>& args);
};
