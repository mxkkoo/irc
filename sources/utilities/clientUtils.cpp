/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:49:04 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/07 14:26:47 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>

std::vector<std::string>	parseLine(std::string& line) {
//Returns a tokenized version of [line]

	std::vector<std::string>	tokens;
	size_t						spacePos;
	size_t						i = 0;

	while (i < line.size()) {
		if (line[i] == ':') {
			tokens.push_back(line.substr(i + 1));
			break;
		}

		spacePos = line.find(' ', i);

		if (spacePos == std::string::npos) {
			tokens.push_back(line.substr(i));
			break;
		}

		if (spacePos != i) {
			tokens.push_back(line.substr(i, spacePos - i));
		}
	}

	return (tokens);
}
