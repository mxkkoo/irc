/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientStatus.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:11:57 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/10 18:45:37 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

bool	Client::hasNickname() {
	if (_nickname.empty()) {
		return (false);
	}
	else {
		return (true);
	}
}

bool	Client::hasUsername() {
	if (_username.empty()) {
		return (false);
	}
	else {
		return (true);
	}
}

bool	Client::isRegistered() {
	if (hasNickname() && hasUsername() && _password) {
		return (true);
	}
	else {
		return (false);
	}
}
