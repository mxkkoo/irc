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
#include "Client.hpp"
#include "utilities.hpp"
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

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

	setupSocket(_listenSocket, _port);

	std::cout << "Server <" << this->_listenSocket << "> connected" << std::endl;

	addFdToPoll(_listenSocket, _pollFds);
	mainLoop();
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
					removeClient(_pollFds[i].fd);
					i --;
				}
			}
		}
	}

	closeSocket(_pollFds);

	std::cout << "Server shutting down" << std::endl;
}

void	Server::newClient() {
//Adds a new client and gives it its own pollFd

	Client				client;
	int					clientFd;
	struct sockaddr_in	clientAddress;
	socklen_t			len;

	len = sizeof(clientAddress);
	clientFd = accept(_listenSocket, (struct sockaddr *) &clientAddress, &len);

	if (clientFd == -1)
		throw (std::runtime_error("accept() failed (client)"));

	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) == -1) {
		close(clientFd);
		throw (std::runtime_error("fcntl() failed (client)"));
	}

	addFdToPoll(clientFd, _pollFds);
	client.setFd(clientFd);
	_clients.insert(std::make_pair(clientFd, client));

	std::cout << "Client " << clientFd << " connected" << std::endl;
}

void	Server::removeClient(int fd) {
//Removes the client from [_pollFds], [_clients] and closes [fd]

	for (size_t i = 0; i < _pollFds.size(); i++) {
		if (_pollFds[i].fd == fd) {
			_pollFds.erase(_pollFds.begin() + i);
			break;
		}
	}

	_clients.erase(fd);
	close(fd);

	std::cout << "Client " << fd << " disconnected" << std::endl;
}

void	Server::receiveData(struct pollfd pollFd) {
//Handles data sent from [pollFd]
	
	char	buff[1024];

	std::memset(buff, 0, sizeof(buff));

	ssize_t	len = recv(pollFd.fd, buff, sizeof(buff) - 1, 0);

	if (len <= 0) {
		throw (std::runtime_error("Client disconnected"));
	}

	Client& client = getClientByFd(pollFd.fd, _clients);

	client.addToBuffer(buff, len);
	client.processBuffer();
}
