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

Client::Client() {

}

Client::~Client() {

}

struct pollfd	Client::getPollFd() {
	return (this->_pollfd);
}
