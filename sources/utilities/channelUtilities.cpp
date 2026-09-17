/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelUtilities.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 19:38:27 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/15 19:49:54 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Channel.hpp"
#include "utilities.hpp"
#include <stdexcept>

void	joinChannel(Client& client, Channel& channel, std::string key) {
//Attempts to make [client] join [channel]

	if (channel.isMember(client)) {
		throw (std::runtime_error("Error"));
	}

	if (channel.isInviteOnly() && !channel.isInvited(client)) {
		sendNumeric(client, "473", channel.getName() + " :Channel is on Invite Only");
		throw (std::runtime_error("Error"));
	}

	if (channel.hasKey() && channel.getKey() != key) {
		sendNumeric(client, "475", channel.getName() + " :Wrong channel key");
		throw (std::runtime_error("Error"));
	}

	if (channel.hasMemberLimit() && channel.getMemberCount() >= channel.getMemberLimit()) {
		sendNumeric(client, "471", channel.getName() + " :Channel is full");
		throw (std::runtime_error("Error"));
	}

	channel.addMember(client);
}
