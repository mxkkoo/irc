/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelMembers.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 17:30:11 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/15 17:42:42 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

bool	Channel::isMember(Client& client) {
	for (size_t i = 0; i < _members.size(); i++) {
		if (client.getFd() == _members[i]) {
			return (true);
		}
	}

	return (false);
}

void	Channel::addMember(Client& client) {
	if (isMember(client)) {
		return;
	}

	_members.push_back(client.getFd());
}

void	Channel::removeMember(Client& client) {
	if (!isMember(client)) {
		return;
	}

	for (size_t i = 0; i < _members.size(); i++) {
		if (client.getFd() == _members[i]) {
			_members.erase(_members.begin() + i);
			return;
		}
	}
}

bool	Channel::isOperator(Client& client) {
	for (size_t i = 0; i < _operators.size(); i++) {
		if (client.getFd() == _operators[i]) {
			return (true);
		}
	}

	return (false);
}

void	Channel::addOperator(Client& client) {
	if (isOperator(client)) {
		return;
	}

	_operators.push_back(client.getFd());
}

void	Channel::removeOperator(Client& client) {
	if (!isOperator(client)) {
		return;
	}

	for (size_t i = 0; i < _operators.size(); i++) {
		if (client.getFd() == _operators[i]) {
			_operators.erase(_operators.begin() + i);
			return;
		}
	}
}
