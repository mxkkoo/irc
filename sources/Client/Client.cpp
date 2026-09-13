/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:21:28 by kyoussou          #+#    #+#             */
/*   Updated: 2026/09/10 18:53:21 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

//Constructors

Client::Client() {

}

Client::~Client() {

}

//Methods

int				Client::getFd() {
	return (_fd);
}

std::string&	Client::getBuffer() {
	return (_buffer);
}

std::string&	Client::getNickname() {
	return (_nickname);
}

std::string&	Client::getUsername() {
	return (_username);
}

void	Client::setFd(int fd) {
	_fd = fd;
}

void	Client::setNickname(std::string nickname) {
	_nickname = nickname;
}

void	Client::setUsername(std::string username, std::string realname) {
	_username = username;
	_realname = realname;
}

void	Client::setPassword(bool password) {
	_password = password;
}

void	Client::appendBuffer(const char* data, size_t len) {
//Appends [data] to the client buffer

	_buffer.append(data, len);
}
