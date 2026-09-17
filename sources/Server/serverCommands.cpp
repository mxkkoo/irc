/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 14:29:06 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/15 17:59:55 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "utilities.hpp"
#include <iostream>
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

void	Server::handlePing(Client& client, std::vector<std::string>& args) {
//Handles "PONG" response

	std::string	token;

	if (args.empty()) {
		token = "";
	}
	else {
		token = args[0];
	}

	sendLine(client.getFd(), "PONG :" + token);

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

void	Server::commandJoin(Client& client, std::vector<std::string>& args) {
//IRC "JOIN" command: makes [client] join/create a channel

	std::vector<std::string>	channels;
	std::vector<std::string>	keys;

	if (!client.isRegistered()) {
		throw (std::runtime_error("Client not registered"));
	}

	if (args.empty()) {
		sendNumeric(client, "461", "JOIN :Not enough parameters");
		return;
	}

	channels = split(args[0], ',');

	if (args.size() > 1) {
		keys = split(args[1], ',');
	}

	for (size_t i = 0; i < channels.size(); i++) {
		std::string	name;
		std::string key;

		name = channels[i];
		
		if (i < keys.size()) {
			key = keys[i];
		}

		if (name.empty() || name[0] != '#') {
			sendNumeric(client, "403", name + " :Invalid channel name");
			continue;
		}

		bool	channelExists; 

		channelExists = (_channels.find(name) != _channels.end());

		if (!channelExists) {
			_channels.insert(std::make_pair(name, Channel(name)));
			_channels[name].addMember(client);
			_channels[name].addOperator(client);
		}
		else {
			Channel&	channel = _channels[name];

			try {
				joinChannel(client, channel, key);
			}
			catch (std::exception& e) {
				continue;
			}
		}

		Channel&	channel = _channels[name];

		channel.broadcast(joinMessage(client, channel), -1);

		if (channel.getTopic().empty()) {
			sendNumeric(client, "331", channel.getName() + " :No topic is set");
		}
		else {
			sendNumeric(client, "332", channel.getName() + " :" + channel.getTopic());
		}
	}
}

void	Server::commandPrivmsg(Client& client, std::vector<std::string>& args) {
//IRC "PRIVMSG" command: handles client messaging

	std::string	recipient;
	std::string	message;
	std::string	line;

	if (!client.isRegistered()) {
		throw (std::runtime_error("Client not registered"));
	}

	if (args.empty()) {
		sendNumeric(client, "411", ":No recipient given");
		return;
	}

	if (args.size() < 2) {
		sendNumeric(client, "412", ":Empty message");
		return;
	}

	recipient = args[0];
	message = args[1];

	if (recipient[0] == '#') {
		if (_channels.find(recipient) == _channels.end()) {
			sendNumeric(client, "403", recipient + " :Channel not found");
			return;
		}

		Channel	&channel = _channels[recipient];

		if (!channel.isMember(client)) {
			sendNumeric(client, "442", recipient + " :You are not a member of this channel");
			return;
		}

		line = ":" + client.getNickname() + "!" + client.getUsername() +
			"@localhost PRIVMSG " + recipient + " :" + message;

		channel.broadcast(line, client.getFd());
	}
	else {
		try {
			Client& targetClient = getClientByNickname(recipient, _clients);
			
			line = ":" + client.getNickname() + "!" + client.getUsername() +
				"@localhost PRIVMSG " + recipient + " :" + message;

			sendLine(targetClient.getFd(), line);
		}
		catch (std::exception& e) {
			sendNumeric(client, "401", recipient + " :User not found");
			return;
		}
	}
}
