/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:42:43 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/10 22:14:43 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Channel.hpp"
#include <poll.h>
#include <vector>
#include <map>

void	setupSocket(int listenSocket, int port);
void	closeSocket(std::vector<struct pollfd>& pollFds);

void		addFdToPoll(int fd, std::vector<struct pollfd>& pollFds);
Client&		getClientByFd(int fd, std::map<int, Client>& clients);
Client&		getClientByNickname(std::string nickname, std::map<int, Client>& clients);

std::vector<std::string>	parseLine(std::string& line);

void	sendLine(int fd, std::string line);
void	sendNumeric(Client& client, std::string code, std::string message);

bool	validNickname(std::string nickname);

void		joinChannel(Client& client, Channel& channel, std::string key);
std::string	joinMessage(Client& client, Channel& channel);

std::vector<std::string>	split(std::string str, char delim);
std::string					toUpper(std::string string);
