/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:36:48 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/15 19:07:18 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "utilities.hpp"
#include <vector>
#include <map>
#include <stdexcept>
#include <poll.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstring>

void	setupSocket(int listenSocket, int port) {
//Sets all necessary options to the server listenSocket

	struct sockaddr_in	servAddress = {};
	int 				enable = 1;

	if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {
		throw (std::runtime_error("setsockopt() error"));
	}
	if (fcntl(listenSocket, F_SETFL, O_NONBLOCK) == -1) {
		throw (std::runtime_error("fcntl() error"));
	}

	std::memset(&servAddress, 0, sizeof(servAddress));

	servAddress.sin_family = AF_INET;
	servAddress.sin_addr.s_addr = INADDR_ANY;
	servAddress.sin_port = htons(port);

	if (bind(listenSocket, (struct sockaddr *) &servAddress, sizeof(sockaddr_in)) == -1) {
		throw (std::runtime_error("bind() error"));
	}
	if (listen(listenSocket, SOMAXCONN) == -1) {
		throw (std::runtime_error("listen() error"));
	}
}

void	closeSocket(std::vector<struct pollfd>& pollFds) {
//Closes the socket and all bound FDs

	for (size_t i = 0; i < pollFds.size(); i++) {
		close(pollFds[i].fd);
	}
}

void	addFdToPoll(int fd, std::vector<struct pollfd>& pollFds) {
//Adds [fd] to the [pollFds] vector

	struct pollfd	newPollFd;

	newPollFd.fd = fd;
	newPollFd.events = POLLIN;
	newPollFd.revents = 0;

	pollFds.push_back(newPollFd);
}

Client&	getClientByFd(int fd, std::map<int, Client>& clients) {
//Returns the client with the corresponding [fd]

	std::map<int, Client>::iterator	it;
	
	it = clients.find(fd);

	if (it == clients.end()) {
		throw (std::runtime_error("Invalid FD"));
	}

	return (it->second);
}

Client&	getClientByNickname(std::string nickname, std::map<int, Client>& clients) {
//Returns the client with the corresponding [nickname]

	std::map<int, Client>::iterator	it;
	
	for (it = clients.begin(); it != clients.end(); ++it) {
		if (it->second.hasNickname() && toUpper(it->second.getNickname()) == toUpper(nickname)) {
			return (it->second);
		}
	}

	throw (std::runtime_error("Invalid Nickname"));
}

std::vector<std::string>	parseLine(std::string& line) {
//Returns a tokenized version of [line]

	std::vector<std::string>	tokens;
	size_t						spacePos;
	size_t						i = 0;

	while (i < line.size()) {
		if (line[i] == ':') {
			tokens.push_back(line.substr(i + 1));
			break;
		}

		spacePos = line.find(' ', i);

		if (spacePos == std::string::npos) {
			tokens.push_back(line.substr(i));
			break;
		}

		if (spacePos != i) {
			tokens.push_back(line.substr(i, spacePos - i));
		}

		i = spacePos + 1;
	}

	return (tokens);
}

void	sendLine(int fd, std::string line) {
//Sends [line] to [fd]

	std::string	message;

	message = line + "\r\n";

	send(fd, message.c_str(), message.size(), 0);
}

void	sendNumeric(Client& client, std::string code, std::string message) {
//Sends a IRC format numeric reply to [client] FD

	std::string	nickname;
	std::string	line;

	if (client.hasNickname()) {
		nickname = client.getNickname();
	}
	else {
		nickname = "*";
	}

	line = ":ircserv " + code + " " + nickname + " " + message;

	sendLine(client.getFd(), line);
}

bool	validNickname(std::string nickname) {
//Checks the validity of [nickname]

	if (nickname.empty() || nickname.size() > 9) {
		return (false);
	}

	if (!std::isalpha(static_cast<unsigned char>(nickname[0]))) {
		return (false);
	}

	for (size_t i = 1; i < nickname.size(); ++i) {
		if (!std::isalnum(static_cast<unsigned char>(nickname[i]))) {
			if (nickname[i] != '-' && nickname[i] != '_') {
				return (false);
			}
		}
	}

	return (true);
}

std::vector<std::string>	split(std::string str, char delim) {
//Returns a vector of parts of [str] split by [delim]

	std::vector<std::string>	tokens;
	size_t						start;
	size_t						end;

	start = 0;
	end = str.find(delim, start);

	while (end != std::string::npos) {
		tokens.push_back(str.substr(start, end - start));
		start = end + 1;
	}

	tokens.push_back(str.substr(start));

	return (tokens);
}

std::string	toUpper(std::string string) {
//Uppercases the string

	std::string	newString;

	newString = string;

	for (size_t i = 0; i < newString.size(); i ++) {
		newString[i] = std::toupper(string[i]);
	}

	return (newString);
}
