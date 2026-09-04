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
}

//Getters

int	Server::getPort() const {
	return (_port);
}

std::string	Server::getPassword() const {
	return (_password);
}

//Methods

bool	Server::_signal = false;

void	Server::handleSignal(int signum) {
	(void) signum;
	std::cout << std::endl;
	Server::_signal = true;
}

void	Server::start() {
//Starts the server; Socket init and setup, then call the main loop to receive data/clients

	_listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (_listenSocket == -1) {
		throw std::runtime_error("socket() error");
	}

	setupSocket();

	std::cout << "Server <" << this->_listenSocket << "> connected" << std::endl;

	addFd(_listenSocket);
	mainLoop();
}

void	Server::setupSocket() {
// Sets all necessary options the server listenSocket

	struct sockaddr_in	servAddress = {};
	int 				enable = 1;

	if (setsockopt(_listenSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {
		throw (std::runtime_error("setsockopt() error"));
	}
	if (fcntl(_listenSocket, F_SETFL, O_NONBLOCK) == -1) {
		throw (std::runtime_error("fcntl() error"));
	}

	std::memset(&servAddress, 0, sizeof(servAddress));
	servAddress.sin_family = AF_INET;
	servAddress.sin_addr.s_addr = INADDR_ANY;
	servAddress.sin_port = htons(this->_port);

	if (bind(_listenSocket, (struct sockaddr *) &servAddress, sizeof(sockaddr_in)) == -1) {
		throw (std::runtime_error("bind() error"));
	}
	if (listen(_listenSocket, SOMAXCONN) == -1) {
		throw (std::runtime_error("listen() error"));
	}
}

void	Server::mainLoop() {
//Main loop; checks FDs for new connections, then incoming data

	while (_signal == false) {
		if (poll(_pollFds.data(), _pollFds.size(), -1) == -1 && Server::_signal == false) {
			throw (std::runtime_error("poll() error"));
		}

		if (_pollFds[0].revents & POLLIN) {
			try {
				newClient();
			}
			catch(std::exception& e) {
				std::cerr << "Connection failed: " << e.what() << std::endl;
			}
		}

		for (size_t i = 1; i < _pollFds.size(); i++) {
			if (_pollFds[i].revents & POLLIN) {
				try {
					receiveData(_pollFds[i]);
				}
				catch(std::exception& e) {
					_pollFds.erase(_pollFds.begin() + i);
					i --;
				}
			}
		}
	}

	closeSocket();
	std::cout << "Server shutting down" << std::endl;
}

void	Server::newClient() {
//Adds a new client and gives it its own pollFd

	Client				client;
	int					clientFd;
	struct sockaddr_in	clientAddress;
	socklen_t			len = sizeof(clientAddress);

	clientFd = accept(_listenSocket, (struct sockaddr *) &clientAddress, &len);

	if (clientFd == -1)
		throw (std::runtime_error("accept() failed (client)"));

	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) == -1) {
		close(clientFd);
		throw (std::runtime_error("fcntl() failed (client)"));
	}

	addFd(clientFd);
	client.setFd(clientFd);
	_clients.push_back(client);

	std::cout << "Client " << clientFd << " connected" << std::endl;
}

void	Server::receiveData(struct pollfd pollFd) {
//Handles data sent from [pollFd]
	
	char	buff[1024];

	memset(buff, 0, sizeof(buff));

	ssize_t	len = recv(pollFd.fd, buff, sizeof(buff) - 1, 0);

	if (len <= 0) {
		std::cout << "Client " << pollFd.fd << " disconnected" << std::endl;
		close(pollFd.fd);
		throw (std::runtime_error("Client disconnected"));
	}

	Client& client = getClientByFd(pollFd.fd);
	client.addToBuffer(buff, len);

	std::cout << "Client " << client.getFd() << " buffer: " << client.getBuffer() << std::endl;
}

//Helpers

void	Server::addFd(int fd) {
//Adds [fd] to the pollFd vector

	struct pollfd	newPollFd;

	newPollFd.fd = fd;
	newPollFd.events = POLLIN;
	newPollFd.revents = 0;
	_pollFds.push_back(newPollFd);
}

void	Server::closeSocket() {
//Closes the socket and all bound FDs

	for (size_t i = 0; i < _pollFds.size(); i++) {
		close(_pollFds[i].fd);
	}
}

Client&	Server::getClientByFd(int fd) {
//Returns the client with the corresponding [fd]

	for (size_t i = 0; i < _clients.size(); i ++) {
		if (_clients[i].getFd() == fd) {
			return (_clients[i]);
		}
	}

	throw (std::runtime_error("Client not found"));
}
