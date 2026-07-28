/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:23:20 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/10 18:31:54 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//Constructors

Server::Server(char* av[]) {
	char*	end;

	_port = strtol(av[1], &end, 10);
	_password = av[2];

	if (_port < 1 || _port > 65535) {
		throw std::invalid_argument("Port must be between 1 and 65535");
	}
}

Server::~Server() {
	close(_listenSocket);
}

//Getters

int	Server::getPort() const {
	return (_port);
}

std::string	Server::getPassword() const {
	return (_password);
}

//Methods

void	Server::start() {
//Starts the server; Socket init and setup, then call the main loop to receive data/clients

	struct pollfd	serverPollFd;

	_listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (_listenSocket == -1) {
		throw std::runtime_error("Socket error");
	}

	setupSocket();

	std::cout << "Server <" << this->_listenSocket << "> connected" << std::endl;

	serverPollFd.fd = this->_listenSocket;
	serverPollFd.events = POLLIN;
	serverPollFd.revents = 0;
	_fds.push_back(serverPollFd);

	mainLoop();
}

void	Server::setupSocket() {
// Sets all necessary options the server listenSocket

	struct sockaddr_in	servAddress = {};
	int 				enable = 1;

	if (setsockopt(this->_listenSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {
		throw (std::runtime_error("Failed to set option SO_REUSEADDR"));
	}
	if (fcntl(this->_listenSocket, F_SETFL, O_NONBLOCK) == -1) {
		throw (std::runtime_error("Failed to set socket as non-blocking"));
	}

	std::memset(&servAddress, 0, sizeof(servAddress));
	servAddress.sin_family = AF_INET;
	servAddress.sin_addr.s_addr = INADDR_ANY;
	servAddress.sin_port = htons(this->_port);

	if (bind(this->_listenSocket, (struct sockaddr *) &servAddress, sizeof(sockaddr_in)) == -1) {
		throw (std::runtime_error("Failed to bind socket"));
	}
	if (listen(this->_listenSocket, SOMAXCONN) == -1) {
		throw (std::runtime_error("Failed to set socket in listening mode"));
	}
}

void	Server::mainLoop() {
//Main loop; checks all sockets using poll() for incoming data or new connections

	while (true) {
		poll(_fds.data(), _fds.size(), -1);
	}
}
