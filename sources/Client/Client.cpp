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

void	Client::setFd(int fd) {
	_fd = fd;
}

void	Client::appendBuffer(const char* data, size_t len) {
//Appends [data] to the client buffer

	_buffer.append(data, len);
}
