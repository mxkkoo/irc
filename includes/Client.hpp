/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:32:10 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/10 18:30:29 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <poll.h>

class Client
{
	private:
		struct pollfd	_pollfd;

	public:
		Client();
		~Client();

		struct pollfd	getPollFd();
};
