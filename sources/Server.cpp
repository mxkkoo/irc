/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:23:20 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/10 16:57:26 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//Constructors

bool	Server::signal = false;

Server::Server(char* av[]) {
	char*	end;

	this->_port = strtol(av[1], &end, 10);
	this->_password = av[2];

	if (this->_port < 1 || this->_port > 65535) {
		throw std::invalid_argument("Port must be between 1 and 65535");
	}
}

Server::~Server() {
	for (size_t i = 0; i < this->_fds.size(); i++) {
		close(this->_fds[i].fd);
	}
}

//Getters

int	Server::getPort() const {
	return (this->_port);
}

std::string	Server::getPassword() const {
	return (this->_password);
}

//Methods

void	Server::handleSignal(int signum) {
	(void) signum;

	std::cout << std::endl << "Signal";
}

void	Server::setupSocket() {
	struct sockaddr_in	servAddress = {};
	struct pollfd		serverPoll;

	//socket creation

	this->_listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (this->_listenSocket == -1)
		throw std::runtime_error("socket error");

	//socket setup

	std::memset(&servAddress, 0, sizeof(servAddress));
	servAddress.sin_family = AF_INET;
	servAddress.sin_addr.s_addr = INADDR_ANY;
	servAddress.sin_port = htons(this->_port);

	int enable = 1;

	if (setsockopt(this->_listenSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
		throw (std::runtime_error("Failed to set option SO_REUSEADDR"));
	if (fcntl(this->_listenSocket, F_SETFL, O_NONBLOCK) == -1)
		throw (std::runtime_error("Failed to set socket as non-blocking"));
	if (bind(this->_listenSocket, (struct sockaddr *) &servAddress, sizeof(sockaddr_in)) == -1)
		throw (std::runtime_error("Failed to bind socket"));
	if (listen(this->_listenSocket, SOMAXCONN) == -1)
		throw (std::runtime_error("Failed to set socket in listening mode"));
	
	serverPoll.fd = this->_listenSocket;
	serverPoll.events = POLLIN;
	serverPoll.revents = 0;

	this->_fds.push_back(serverPoll);
}

//TODO: put the poll stuffs in a utils func

void	Server::start() {
	setupSocket();

	std::cout << "Server <" << this->_listenSocket << "> Connected" << std::endl;

	while (Server::signal == false) {
		if (poll(&(this->_fds[0]), _fds.size(), -1) == -1 && Server::signal == false)
			throw(std::runtime_error("Failed to poll()"));

		for (size_t i = 0; i < this->_fds.size(); i++) {
			if (this->_fds[i].revents && POLLIN) {
				if (this->_fds[i].fd == this->_listenSocket) {
					std::cout << "connection received" << std::endl;
				}
			}
		}
	}
}
