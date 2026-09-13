/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 14:29:06 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/10 22:13:45 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "utilities.hpp"
#include <stdexcept>

void	Server::handleCap(Client& client, std::vector<std::string>& args) {
//Handles "CAP" response gracefully

	if (!args.empty()) {
		if (args[0] == "LS") {
			sendLine(client.getFd(), "CAP * LS :");
		}
	}

	return; 
}

void	Server::commandPass(Client& client, std::vector<std::string>& args) {
//IRC "PASS" command: Registers [client] on password entry

	if (client.isRegistered()) {
		sendNumeric(client, "462", ":You are already registered");
		return;
	}

	if (args.empty()) {
		sendNumeric(client, "461", "PASS :Not enough parameters");
		return;
	}

	if (args[0] != _password) {
		sendNumeric(client, "464", ":Password is incorrect");
		throw (std::runtime_error("Client entered wrong password"));
		return;
	}

	client.setPassword(true);
}

void	Server::commandUser(Client& client, std::vector<std::string>& args) {
//IRC "USER" command: sets [client] username

	if (!client.getUsername().empty()) {
		sendNumeric(client, "462", ":You are already registered");
		return;
	}

	if (args.size() < 4) {
		sendNumeric(client, "461", "USER :Not enough parameters");
		return;
	}
	
	client.setUsername(args[0], args[3]);
}

void	Server::commandNick(Client& client, std::vector<std::string>& args) {
//IRC "NICK" command: sets [client] nickname

	std::string	currentNickname;

	if (args.empty()) {
		sendNumeric(client, "431", ":No nickname given");
		return;
	}

	if (!validNickname(args[0])) {
		sendNumeric(client, "432", args[0] + " :Nickname Invalid");
		return;
	}

	try {
		Client& other = getClientByNickname(args[0], _clients);

		if (other.getFd() != client.getFd()) {
			sendNumeric(client, "433", args[0] + " :Nickname is already in use");
			return;
		}
	}
	catch (std::exception& e) {
	}

	currentNickname = client.getNickname();

	client.setNickname(args[0]);

	if (!currentNickname.empty() && currentNickname != args[0]) {
		sendLine(client.getFd(), ":" + currentNickname + " NICK :" + args[0]);
	}
}
