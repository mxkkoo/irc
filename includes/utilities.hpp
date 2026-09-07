/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:42:43 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/04 15:46:47 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include <poll.h>
#include <vector>
#include <map>

//Server Utils

void	setupSocket(int listenSocket, int port);
void	closeSocket(std::vector<struct pollfd>& pollFds);

void	addFdToPoll(int fd, std::vector<struct pollfd>& pollFds);
Client&	getClientByFd(int fd, std::map<int, Client>& clients);

//Client Utils

std::vector<std::string>	parseLine(std::string& line);
