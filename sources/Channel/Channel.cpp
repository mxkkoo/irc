/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 17:14:07 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/15 17:50:42 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//Constructors

Channel::Channel() {
}

Channel::Channel(std::string name) {
	_name = name;
	_topic = "";

	_key = "";
	_memberLimit = 0;
	_inviteOnly = false;
}

Channel::~Channel() {
}

//Methods

std::string	Channel::getName() {
	return (_name);
}

std::string	Channel::getTopic() {
	return (_topic);
}

std::string	Channel::getKey() {
	return (_key);
}

size_t		Channel::getMemberCount() {
	return (_members.size());
}

size_t		Channel::getMemberLimit() {
	return (_memberLimit);
}
