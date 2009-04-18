//////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////

#ifndef __OTSERV_CHAT_H__
#define __OTSERV_CHAT_H__
#include "otsystem.h"
#include "const.h"

#include <fstream>
#include "party.h"

class Player;

typedef std::list<uint32_t> UsersList;

class ChatChannel
{
	public:
		ChatChannel(uint16_t channelId, std::string channelName)
		{
			m_id = channelId;
			m_name = channelName;
			m_logged = false;
			m_enabled = true;
			m_access = 0;
		}
		virtual ~ChatChannel() {}

		bool configure(xmlNodePtr p);
		const uint16_t getId() {return m_id;}
		const std::string& getName() {return m_name;}

		const UsersList& getUsers() {return m_users;}
		virtual const uint32_t getOwner() {return 0;}

		uint16_t getAccess() const {return m_access;}
		bool isLogged() const {return m_logged;}
		bool isEnabled() const {return m_enabled;}

		bool addUser(Player* player);
		bool removeUser(Player* player);

		bool talk(Player* player, SpeakClasses type, const std::string& text, uint32_t time = 0);

	protected:
		std::string m_name;

		bool m_logged, m_enabled;
		uint16_t m_id, m_access;

		UsersList m_users;
		boost::shared_ptr<std::ofstream> m_file;
};

class PrivateChatChannel : public ChatChannel
{
	public:
		PrivateChatChannel(uint16_t channelId, std::string channelName);
		virtual ~PrivateChatChannel(){}

		virtual const uint32_t getOwner() {return m_owner;}
		void setOwner(uint32_t id) {m_owner = id;}

		bool isInvited(const Player* player);

		void invitePlayer(Player* player, Player* invitePlayer);
		void excludePlayer(Player* player, Player* excludePlayer);

		bool addInvited(Player* player);
		bool removeInvited(Player* player);

		void closeChannel();

	protected:
		UsersList m_invites;
		uint32_t m_owner;
};

typedef std::list<ChatChannel*> ChannelList;

class Chat
{
	public:
		Chat();
		virtual ~Chat();

		void reload();
		bool loadFromXml();
		bool parseChannelNode(xmlNodePtr p);

		ChatChannel* createChannel(Player* player, uint16_t channelId);
		bool deleteChannel(Player* player, uint16_t channelId);

		ChatChannel* addUserToChannel(Player* player, uint16_t channelId);
		bool removeUserFromChannel(Player* player, uint16_t channelId);
		void removeUserFromAllChannels(Player* player);

		bool talkToChannel(Player* player, SpeakClasses type, const std::string& text, unsigned short channelId);

		ChatChannel* getChannel(Player* player, uint16_t channelId);
		std::string getChannelName(Player* player, uint16_t channelId);
		ChatChannel* getChannelById(uint16_t channelId);

		ChannelList getChannelList(Player* player);
		PrivateChatChannel* getPrivateChannel(Player* player);

	private:
		ChatChannel* dummyPrivate;

		typedef std::map<uint16_t, ChatChannel*> NormalChannelMap;
		NormalChannelMap m_normalChannels;

		typedef std::map<uint16_t, PrivateChatChannel*> PrivateChannelMap;
		PrivateChannelMap m_privateChannels;

		typedef std::map<Party*, ChatChannel*> PartyChannelMap;
		PartyChannelMap m_partyChannels;

		typedef std::map<uint32_t, ChatChannel*> GuildChannelMap;
		GuildChannelMap m_guildChannels;
};

#endif
