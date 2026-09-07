/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:21:28 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/10 18:30:16 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "utilities.hpp"
#include <iostream>
#include <vector>

//Constructors

Client::Client() {

}

Client::~Client() {

}

//Getters

int				Client::getFd() {
	return (_fd);
}

std::string&	Client::getBuffer() {
	return (_buffer);
}

//Methods

void	Client::setFd(int fd) {
	_fd = fd;
}

void	Client::addToBuffer(const char* data, size_t len) {
//Appends [data] to the client buffer

	_buffer.append(data, len);
}

void	Client::processBuffer() {
//Processes the buffer; extracts lines
	
	std::string	line;
	size_t		pos;

	pos = _buffer.find('\n');

	while (pos != std::string::npos) {
		line = _buffer.substr(0, pos);

		if (!line.empty() && line[line.size() - 1] == '\r') {
			line.erase(line.size() - 1);
		}

		_buffer.erase(0, pos + 1);
		
		if (!line.empty())
			std::cout << line << std::endl; //handleLine goes here

		pos = _buffer.find('\n');
	}
}

void	Client::processLine(std::string& line) {
//Processes lines extracted from the buffer; tokenizes and dispatch lines

	std::vector<std::string>	tokens;
	std::string					command;

	tokens = parseLine(line);

	if (tokens.empty())
		return;

	command = tokens[0];

	tokens.erase(tokens.begin());
}
