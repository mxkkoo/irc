/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelyan <kyoussou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 16:25:34 by kelyan            #+#    #+#             */
/*   Updated: 2026/09/15 17:48:37 by kelyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include <string>
#include <vector>

class	Channel {
//Channel class: Channel specific informations and methods

	private:
		std::vector<int>	_operators;
		std::vector<int>	_members;
		std::vector<int>	_invited;
		std::string			_name;
		std::string			_topic;

		std::string			_key;
		size_t 				_memberLimit;
		bool				_inviteOnly;

	public:
		Channel();
		Channel(std::string name);
		~Channel();

		std::string			getName();
		std::string			getTopic();
		std::string			getKey();
		size_t				getMemberCount();
		size_t				getMemberLimit();
		std::vector<int>	getMembers();

		void		broadcast(std::string line, int excludeFd);

		bool		isMember(Client& client);
		void		addMember(Client& client);
		void		removeMember(Client& client);

		bool		isOperator(Client& client);
		void		addOperator(Client& client);
		void		removeOperator(Client& client);

		bool		isInvited(Client& client);
		void		addInvited(Client& client);
		void		removeInvited(Client& client);

		void		setTopic(std::string topic);

		bool		isInviteOnly();
		void		setInviteOnly(bool status);		

		bool		hasKey();
		void		setKey(std::string key);

		bool		hasMemberLimit();
		void		setLimit(size_t limit);
};
