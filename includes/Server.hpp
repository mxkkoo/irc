/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classes.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoussou <kyoussou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:10:08 by kyoussou          #+#    #+#             */
/*   Updated: 2026/07/07 14:19:52 by kyoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Server
{
	private:
		int			_port;
		std::string	_password;

		int			_listenSocket;

	public:
		Server(char* av[]);

		int			getPort() const;
		std::string	getPassword() const;
		
		void		setupSocket();
		void		start();
};
