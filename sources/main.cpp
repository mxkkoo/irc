/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:19:59 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/07 14:20:54 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <cstdlib>

int	main(int ac, char* av[]) {
	try {	
		if (ac != 3)
			throw (std::invalid_argument("./ircserv [port] [password]"));
		
		Server	serv(av);
		std::cout << "port: " << serv.getPort() << ", password: " << serv.getPassword() << std::endl;
		serv.start();
	}

	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
