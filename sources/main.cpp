/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:19:59 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/10 16:56:25 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <signal.h>

int	main(int ac, char* av[]) {
//Checks arg format, sets the signal handler then starts the server

	if (ac != 3) {
		std::cerr << "format: ./ircserv [port] [password]" << std::endl;
		return (1);
	}

	Server	serv(av);

	signal(SIGINT, Server::handleSignal);
	signal(SIGQUIT, Server::handleSignal);

	try {
		serv.start();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (2);
	}

	return (0);
}
