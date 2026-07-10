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

int	main(int ac, char* av[]) {
	try {	
		if (ac != 3)
			throw (std::invalid_argument("./ircserv [port] [password]"));
		
		Server	serv(av);
		std::cout << "port: " << serv.getPort() << ", password: " << serv.getPassword() << std::endl;
		//signal(SIGINT, Server::handleSignal);
		serv.start();
	}

	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
