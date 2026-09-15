/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 17:42:20 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/15 17:50:13 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

void	Channel::setTopic(std::string topic) {
	_topic = topic;
}

bool	Channel::isInviteOnly() {
	return (_inviteOnly);
}

void	Channel::setInviteOnly(bool status) {
	_inviteOnly = status;
}

bool	Channel::hasKey() {
	return (!_key.empty());
}

void	Channel::setKey(std::string key) {
	_key = key;
}

bool	Channel::hasMemberLimit() {
	return (_memberLimit != 0);
}

void	Channel::setLimit(size_t limit) {
	_memberLimit = limit;
}
