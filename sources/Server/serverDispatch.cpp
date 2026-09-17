/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverDispatch.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 13:17:30 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/09 13:42:51 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "utilities.hpp"

void	Server::processBuffer(Client& client) {
//Extracts lines from [client] buffer then processes them
	
	std::string&	buffer = client.getBuffer();
	std::string		line;
	size_t			pos;

	pos = buffer.find('\n');

	while (pos != std::string::npos) {
		line = buffer.substr(0, pos);

		if (!line.empty() && line[line.size() - 1] == '\r') {
			line.erase(line.size() - 1);
		}

		buffer.erase(0, pos + 1);
		
		if (!line.empty()) {
			processLine(client, line);
		}

		pos = buffer.find('\n');
	}
}

void	Server::processLine(Client& client, std::string& line) {
//Tokenizes and dispatch [line] extracted from [client] buffer

	std::vector<std::string>	tokens;
	std::string					command;

	tokens = parseLine(line);

	if (tokens.empty())
		return;

	command = toUpper(tokens[0]);

	tokens.erase(tokens.begin());
	dispatch(client, command, tokens);
}

void	Server::dispatch(Client& client, std::string command, std::vector<std::string> args) {
//Executes [command] with given [args]

	bool	wasRegistered;

	wasRegistered = client.isRegistered();

	if (command == "QUIT")
		commandQuit(client, args);

	try {
		if (command == "CAP") {
			handleCap(client, args);
		}
		else if (command == "PING") {
			handlePing(client, args);
		}
		else if (command == "PASS") {
			commandPass(client, args);
		}
		else if (command == "NICK") {
			commandNick(client, args);
		}
		else if (command == "USER") {
			commandUser(client, args);
		}
		else if (command == "JOIN") {
			commandJoin(client, args);
		}
		else if (command == "PRIVMSG") {
			commandPrivmsg(client, args);
		}
		else
			sendNumeric(client, "421", command + " :Unknown command");
	}
	catch (std::exception& e) {
		sendNumeric(client, "451", ":You are not registered");
	}

	if (!wasRegistered && client.isRegistered()) {
		sendNumeric(client, "001", ":Welcome to the IRC server");
	}
}
