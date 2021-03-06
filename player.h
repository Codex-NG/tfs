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

#ifndef __OTSERV_PLAYER_H__
#define __OTSERV_PLAYER_H__

#include "otsystem.h"
#include "creature.h"
#include "container.h"
#include "cylinder.h"
#include "outfit.h"
#include "enums.h"
#include "vocation.h"
#include "protocolgame.h"
#include "ioguild.h"
#include "party.h"
#include "inbox.h"
#include "depotchest.h"
#include "depotlocker.h"

#include <vector>
#include <ctime>
#include <algorithm>

class House;
class NetworkMessage;
class Weapon;
class ProtocolGame;
class Npc;
class Party;
class SchedulerTask;
class Bed;

enum skillsid_t
{
	SKILL_LEVEL = 0,
	SKILL_TRIES = 1,
	SKILL_PERCENT = 2
};

enum playerinfo_t
{
	PLAYERINFO_LEVEL,
	PLAYERINFO_LEVELPERCENT,
	PLAYERINFO_HEALTH,
	PLAYERINFO_MAXHEALTH,
	PLAYERINFO_MANA,
	PLAYERINFO_MAXMANA,
	PLAYERINFO_MAGICLEVEL,
	PLAYERINFO_MAGICLEVELPERCENT,
	PLAYERINFO_SOUL,
};

enum freeslot_t
{
	SLOT_TYPE_NONE,
	SLOT_TYPE_INVENTORY,
	SLOT_TYPE_CONTAINER
};

enum chaseMode_t
{
	CHASEMODE_STANDSTILL,
	CHASEMODE_FOLLOW,
};

enum fightMode_t
{
	FIGHTMODE_ATTACK,
	FIGHTMODE_BALANCED,
	FIGHTMODE_DEFENSE
};

enum secureMode_t
{
	SECUREMODE_ON,
	SECUREMODE_OFF
};

enum tradestate_t
{
	TRADE_NONE,
	TRADE_INITIATED,
	TRADE_ACCEPT,
	TRADE_ACKNOWLEDGE,
	TRADE_TRANSFER
};

struct AccountManager
{
	uint32_t realAccount, newVocation;
	int8_t talkState;
	bool managingAccount;
	PlayerSex_t newSex;
	std::string newAccountName, accountManagerInput, namelockedPlayerName;

	AccountManager()
	{
		managingAccount = false;
		namelockedPlayerName = "";
		talkState = 0;
		newVocation = VOCATION_NONE;
		newSex = PLAYERSEX_FEMALE;
	}
};

struct VIPEntry
{
	uint32_t guid;
	std::string name;
	std::string description;
	uint32_t icon;
	bool notify;
};

typedef std::pair<uint32_t, Container*> containervector_pair;
typedef std::vector<containervector_pair> ContainerVector;
typedef std::map<uint32_t, DepotChest*> DepotMap;
typedef std::map<uint32_t, DepotLocker*> DepotLockerMap;
typedef std::map<uint32_t, int32_t> StorageMap;
typedef OTSERV_HASH_SET<uint32_t> VIPListSet;
typedef std::map<uint32_t, uint32_t> MuteCountMap;
typedef std::list<std::string> LearnedInstantSpellList;
typedef std::list<uint32_t> InvitedToGuildsList;
typedef std::list<uint32_t> GuildWarList;
typedef std::list<Party*> PartyList;

#define PLAYER_MAX_SPEED 1500
#define PLAYER_MIN_SPEED 10

class Player : public Creature, public Cylinder
{
	public:
#ifdef __ENABLE_SERVER_DIAGNOSTIC__
		static uint32_t playerCount;
#endif
		Player(const std::string& name, ProtocolGame* p);
		virtual ~Player();

		virtual Player* getPlayer() {return this;}
		virtual const Player* getPlayer() const {return this;}

		static MuteCountMap muteCountMap;
		static int32_t maxMessageBuffer;

		virtual const std::string& getName() const {return name;}
		virtual const std::string& getNameDescription() const {return name;}
		virtual std::string getDescription(int32_t lookDistance) const;

		virtual CreatureType_t getType() const {return CREATURETYPE_PLAYER;}

		uint8_t getCurrentMount() const;
		void setCurrentMount(uint8_t mountId);
		bool isMounted() const { return defaultOutfit.lookMount != 0; }
		bool toggleMount(bool mount);
		bool tameMount(uint8_t mountId);
		bool untameMount(uint8_t mountId);
		void dismount();

		void setDepotChange(bool b) {depotChange = b;}

		void manageAccount(const std::string& text);

		void sendFYIBox(const std::string& message)
			{if(client) client->sendFYIBox(message);}

		void setGUID(uint32_t _guid) {guid = _guid;}
		uint32_t getGUID() const {return guid;}
		virtual uint32_t idRange() {return 0x10000000;}
		virtual bool canSeeInvisibility() const {return hasFlag(PlayerFlag_CanSenseInvisibility) || accessLevel;}
		static AutoList<Player> listPlayer;
		void removeList();
		void addList();
		void kickPlayer(bool displayEffect);

		static uint64_t getExpForLevel(int32_t lv)
		{
			lv--;
			return ((50ULL * lv * lv * lv) - (150ULL * lv * lv) + (400ULL * lv)) / 3ULL;
		}

		uint16_t getStaminaMinutes() const { return staminaMinutes; }
		void regenerateStamina(int32_t offlineTime);
		void useStamina();

		bool addOfflineTrainingTries(skills_t skill, int32_t tries);

		void addOfflineTrainingTime(int32_t addTime) { offlineTrainingTime = std::min(12 * 3600 * 1000, offlineTrainingTime + addTime); }
		void removeOfflineTrainingTime(int32_t removeTime) { offlineTrainingTime = std::max(0, offlineTrainingTime - removeTime); }
		int32_t getOfflineTrainingTime() const { return offlineTrainingTime; }

		int32_t getOfflineTrainingSkill() const { return offlineTrainingSkill; }
		void setOfflineTrainingSkill(int32_t skill) { offlineTrainingSkill = skill; }

		uint64_t getBankBalance() const {return bankBalance;}
		void setBankBalance(uint64_t balance) {bankBalance = balance;}

		uint32_t getGuildId() const {return guildId;}
		void setGuildId(uint32_t newGuildId) {guildId = newGuildId;}

		int8_t getGuildLevel() const {return guildLevel;}
		void setGuildLevel(GuildLevel_t newGuildLevel);

		bool isGuildMate(const Player* player) const;

		void setLastWalkthroughAttempt(int64_t walkthroughAttempt) { lastWalkthroughAttempt = walkthroughAttempt; }
		void setLastWalkthroughPosition(Position walkthroughPosition) { lastWalkthroughPosition = walkthroughPosition; }

		bool hasRequestedOutfit() const {return requestedOutfit;}
		void hasRequestedOutfit(bool newValue) {requestedOutfit = newValue;}

		Inbox* getInbox() const { return inbox; }
		const DepotMap& getDepotChests() const { return depotChests; }

		uint32_t getClientIcons() const;

		GuildWarList getGuildWarList() const {return guildWarList;}
		void setGuildWarList(GuildWarList _guildWarList) {guildWarList = _guildWarList;}

		Vocation* getVocation() const {return vocation;}

		OperatingSystem_t getOperatingSystem() const {return operatingSystem;}
		void setOperatingSystem(OperatingSystem_t clientos) {operatingSystem = clientos;}

		uint16_t getProtocolVersion() const {return protocolVersion;}
		void setProtocolVersion(uint16_t protocolversion) {protocolVersion = protocolversion;}

		secureMode_t getSecureMode() const {return secureMode;}

		void setParty(Party* _party) {party = _party;}
		Party* getParty() const {return party;}
		PartyShields_t getPartyShield(const Player* player) const;
		bool isInviting(const Player* player) const;
		bool isPartner(const Player* player) const;
		void sendPlayerPartyIcons(Player* player);
		bool addPartyInvitation(Party* party);
		bool removePartyInvitation(Party* party);
		void clearPartyInvitations();

		GuildEmblems_t getGuildEmblem(const Player* player) const;

		uint64_t getSpentMana() const {return manaSpent;}
		const std::string& getGuildName() const {return guildName;}
		void setGuildName(const std::string& guildname) {guildName = guildname;}
		const std::string& getGuildRank() const {return guildRank;}
		void setGuildRank(const std::string& rank) {guildRank = rank;}
		const std::string& getGuildNick() const {return guildNick;}
		void setGuildNick(const std::string& nick) {guildNick = nick;}

		bool isInWar(const Player* player) const;
		bool isInWarList(uint32_t guild_id) const;
		bool isInvitedToGuild(uint32_t guild_id) const;
		void leaveGuild();

		void setFlags(uint64_t flags){groupFlags = flags;}
		bool hasFlag(PlayerFlags value) const {return (0 != (groupFlags & ((uint64_t)1 << value)));}

		BedItem* getBedItem() { return bedItem; }
		void setBedItem(BedItem* b) { bedItem = b; }

		void addBlessing(int16_t blessing) {blessings += blessing;}
		bool hasBlessing(int16_t value) const {return (0 != (blessings & ((int16_t)1 << value)));}

		bool isFemale() const {return sex == PLAYERSEX_FEMALE;}
		bool isMale() const {return sex == PLAYERSEX_MALE;}

		bool isOffline() const {return (getID() == 0);}
		void disconnect() {if(client) client->disconnect();}
		uint32_t getIP() const;

		void addContainer(uint32_t cid, Container* container);
		void closeContainer(uint32_t cid);
		int32_t getContainerID(const Container* container) const;
		Container* getContainer(uint32_t cid);

		bool canOpenCorpse(uint32_t ownerId);

		void addStorageValue(const uint32_t key, const int32_t value, const bool isLogin = false);
		bool getStorageValue(const uint32_t key, int32_t& value) const;
		void genReservedStorageRange();

		inline StorageMap::const_iterator getStorageIteratorBegin() const {return storageMap.begin();}
		inline StorageMap::const_iterator getStorageIteratorEnd() const {return storageMap.end();}

		void setGroupId(int32_t newId);
		int32_t getGroupId() const {return groupId;}

		void setMarketDepotId(int16_t newId) { marketDepotId = newId; }
		int16_t getMarketDepotId() const { return marketDepotId; }

		void setLastDepotId(int16_t newId) { lastDepotId = newId; }
		int16_t getLastDepotId() const { return lastDepotId; }

		void resetIdleTime() {idleTime = 0;}
		bool getNoMove() const {return mayNotMove;}

		bool isAccountManager() const {return accountManager != NULL;}
		void setAccountManager() { if(accountManager == NULL) accountManager = new AccountManager();}
		AccountManager* getAccountManager() const {return accountManager;}

		bool isInGhostMode() const {return ghostMode;}
		void switchGhostMode() {ghostMode = !ghostMode;}

		uint32_t getAccount() const {return accountNumber;}
		AccountType_t getAccountType() const {return accountType;}
		uint32_t getLevel() const {return level;}
		int32_t getMagicLevel() const {return getPlayerInfo(PLAYERINFO_MAGICLEVEL);}
		uint32_t getBaseMagicLevel() const {return magLevel;}
		bool isAccessPlayer() const {return accessLevel;}
		bool isPremium() const;
		void setPremiumDays(int32_t v);

		void setVocation(uint32_t vocId);
		uint32_t getVocationId() const {return vocationId;}

		PlayerSex_t getSex() const {return sex;}
		void setSex(PlayerSex_t);
		int32_t getPlayerInfo(playerinfo_t playerinfo) const;
		uint64_t getExperience() const {return experience;}

		time_t getLastLoginSaved() const {return lastLoginSaved;}

		time_t getLastLogout() const {return lastLogout;}

		const Position& getLoginPosition() const {return loginPosition;}
		const Position& getTemplePosition() const {return masterPos;}
		uint32_t getTown() const {return town;}
		void setTown(uint32_t _town) {town = _town;}

		void clearModalWindows();
		bool hasModalWindowOpen(uint32_t modalWindowId) const;
		void onModalWindowHandled(uint32_t modalWindowId);

		virtual bool isPushable() const;
		virtual int32_t getThrowRange() const {return 1;}
		uint32_t isMuted();
		void addMessageBuffer();
		void removeMessageBuffer();

		double getCapacity() const
		{
			if(hasFlag(PlayerFlag_CannotPickupItem))
				return 0.00;
			else if(hasFlag(PlayerFlag_HasInfiniteCapacity))
				return 10000.00;
			else
				return capacity;
		}

		double getFreeCapacity() const
		{
			if(hasFlag(PlayerFlag_CannotPickupItem))
				return 0.00;
			else if(hasFlag(PlayerFlag_HasInfiniteCapacity))
				return 10000.00;
			else
				return std::max(0.00, capacity - inventoryWeight);
		}

		virtual int32_t getMaxHealth() const {return getPlayerInfo(PLAYERINFO_MAXHEALTH);}
		virtual int32_t getMaxMana() const {return getPlayerInfo(PLAYERINFO_MAXMANA);}

		Item* getInventoryItem(slots_t slot) const;

		bool isItemAbilityEnabled(slots_t slot) const {return inventoryAbilities[slot];}
		void setItemAbility(slots_t slot, bool enabled) {inventoryAbilities[slot] = enabled;}

		int32_t getBaseSkill(skills_t skill) const {return skills[skill][SKILL_LEVEL];}

		int32_t getVarSkill(skills_t skill) const {return varSkills[skill];}
		void setVarSkill(skills_t skill, int32_t modifier) {varSkills[skill] += modifier;}

		int32_t getVarStats(stats_t stat) const {return varStats[stat];}
		void setVarStats(stats_t stat, int32_t modifier);
		int32_t getDefaultStats(stats_t stat);

		void setConditionSuppressions(uint32_t conditions, bool remove);

		DepotChest* getDepotChest(uint32_t depotId, bool autoCreate);
		DepotLocker* getDepotLocker(uint32_t depotId);
		void onReceiveMail();
		bool isNearDepotBox();

		virtual bool canSee(const Position& pos) const;
		virtual bool canSeeCreature(const Creature* creature) const;

		bool canWalkthrough(const Creature* creature) const;
		bool canWalkthroughEx(const Creature* creature) const;

		virtual RaceType_t getRace() const {return RACE_BLOOD;}

		//safe-trade functions
		void setTradeState(tradestate_t state) {tradeState = state;}
		tradestate_t getTradeState() {return tradeState;}
		Item* getTradeItem() {return tradeItem;}

		//shop functions
		void setShopOwner(Npc* owner, int32_t onBuy, int32_t onSell)
		{
			shopOwner = owner;
			purchaseCallback = onBuy;
			saleCallback = onSell;
		}

		Npc* getShopOwner(int32_t& onBuy, int32_t& onSell)
		{
			onBuy = purchaseCallback;
			onSell = saleCallback;
			return shopOwner;
		}

		const Npc* getShopOwner(int32_t& onBuy, int32_t& onSell) const
		{
			onBuy = purchaseCallback;
			onSell = saleCallback;
			return shopOwner;
		}

		//V.I.P. functions
		void notifyStatusChange(Player* player, VipStatus_t status);
		bool removeVIP(uint32_t guid);
		bool addVIP(uint32_t guid, std::string& name, VipStatus_t status);
		bool addVIPInternal(uint32_t guid);
		bool editVIP(uint32_t _guid, const std::string& description, uint32_t icon, bool notify);

		//follow functions
		virtual bool setFollowCreature(Creature* creature, bool fullPathSearch = false);
		virtual void goToFollowCreature();

		//follow events
		virtual void onFollowCreature(const Creature* creature);

		//walk events
		virtual void onWalk(Direction& dir);
		virtual void onWalkAborted();
		virtual void onWalkComplete();

		void stopWalk();
		void openShopWindow(Npc* npc, const std::list<ShopInfo>& shop);
		void closeShopWindow(bool sendCloseShopWindow = true);
		void updateSaleShopList(uint32_t itemId);
		bool hasShopItemForSale(uint32_t itemId, uint8_t subType);

		void setChaseMode(chaseMode_t mode);
		void setFightMode(fightMode_t mode);
		void setSecureMode(secureMode_t mode) {secureMode = mode;}

		//combat functions
		virtual bool setAttackedCreature(Creature* creature);
		bool isImmune(CombatType_t type) const;
		bool isImmune(ConditionType_t type) const;
		bool hasShield() const;
		virtual bool isAttackable() const;

		virtual void changeHealth(int32_t healthChange, bool sendHealthChange = true);
		virtual void changeMana(int32_t manaChange);
		void changeSoul(int32_t soulChange);

		bool isPzLocked() const { return pzLocked; }
		virtual BlockType_t blockHit(Creature* attacker, CombatType_t combatType, int32_t& damage,
			bool checkDefense = false, bool checkArmor = false);
		virtual void doAttacking(uint32_t interval);
		virtual bool hasExtraSwing() {return lastAttack > 0 && ((OTSYS_TIME() - lastAttack) >= getAttackSpeed());}
		int32_t getShootRange() const {return shootRange;}

		int32_t getSkill(skills_t skilltype, skillsid_t skillinfo) const;
		bool getAddAttackSkill() const {return addAttackSkillPoint;}
		BlockType_t getLastAttackBlockType() const {return lastAttackBlockType;}

		Item* getWeapon(bool ignoreAmmo = false);
		virtual WeaponType_t getWeaponType();
		int32_t getWeaponSkill(const Item* item) const;
		void getShieldAndWeapon(const Item* &shield, const Item* &weapon) const;

		virtual void drainHealth(Creature* attacker, CombatType_t combatType, int32_t damage);
		virtual void drainMana(Creature* attacker, int32_t manaLoss);
		void addManaSpent(uint64_t amount, bool withMultiplier = true);
		void addSkillAdvance(skills_t skill, uint32_t count);

		virtual int32_t getArmor() const;
		virtual int32_t getDefense() const;
		virtual float getAttackFactor() const;
		virtual float getDefenseFactor() const;

		void addWeaponExhaust(uint32_t ticks);
		void addCombatExhaust(uint32_t ticks);
		void addHealExhaust(uint32_t ticks);
		void addInFightTicks(bool pzlock = false);
		void addDefaultRegeneration(uint32_t addTicks);

		virtual uint64_t getGainedExperience(Creature* attacker) const;

		//combat event functions
		virtual void onAddCondition(ConditionType_t type);
		virtual void onAddCombatCondition(ConditionType_t type);
		virtual void onEndCondition(ConditionType_t type);
		virtual void onCombatRemoveCondition(const Creature* attacker, Condition* condition);
		virtual void onAttackedCreature(Creature* target);
		virtual void onAttacked();
		virtual void onAttackedCreatureDrainHealth(Creature* target, int32_t points);
		virtual void onTargetCreatureGainHealth(Creature* target, int32_t points);
		virtual bool onKilledCreature(Creature* target, bool lastHit = true);
		virtual void onGainExperience(uint64_t gainExp, Creature* target);
		virtual void onGainSharedExperience(uint64_t gainExp);
		virtual void onAttackedCreatureBlockHit(Creature* target, BlockType_t blockType);
		virtual void onBlockHit(BlockType_t blockType);
		virtual void onChangeZone(ZoneType_t zone);
		virtual void onAttackedCreatureChangeZone(ZoneType_t zone);
		virtual void onIdleStatus();
		virtual void onPlacedCreature();
		virtual void onRemovedCreature();

		virtual void getCreatureLight(LightInfo& light) const;

		Skulls_t getSkull() const;
		Skulls_t getSkullClient(const Player* player) const;

		bool hasAttacked(const Player* attacked) const;
		void addAttacked(const Player* attacked);
		void clearAttacked();
		void addUnjustifiedDead(const Player* attacked);
		void setSkull(Skulls_t newSkull) {skull = newSkull;}
		void sendCreatureSkull(const Creature* creature) const
			{if(client) client->sendCreatureSkull(creature);}
		void checkSkullTicks(int32_t ticks);

		const OutfitListType& getPlayerOutfits();
		bool canWear(uint32_t _looktype, uint32_t _addons);
		void addOutfit(uint32_t _looktype, uint32_t _addons);
		bool remOutfit(uint32_t _looktype, uint32_t _addons);
		uint32_t getOutfitAddons(uint32_t looktype);
		bool canLogout();

		//tile
		//send methods
		void sendAddTileItem(const Tile* tile, const Position& pos, const Item* item)
			{if(client) client->sendAddTileItem(tile, pos, tile->getClientIndexOfThing(this, item), item);}
		void sendUpdateTileItem(const Tile* tile, const Position& pos, const Item* olditem, const Item* newitem)
			{if(client) client->sendUpdateTileItem(tile, pos, tile->getClientIndexOfThing(this, newitem), newitem);}
		void sendRemoveTileItem(const Tile* tile, const Position& pos, uint32_t stackpos, const Item* item)
			{if(client) client->sendRemoveTileItem(tile, pos, stackpos);}
		void sendUpdateTile(const Tile* tile, const Position& pos)
			{if(client) client->sendUpdateTile(tile, pos);}

		void sendChannelMessage(const std::string& author, const std::string& text, SpeakClasses type, uint16_t channel)
			{if(client) client->sendChannelMessage(author, text, type, channel);}
		void sendChannelEvent(uint16_t channelId, const std::string& playerName, ChannelEvent_t channelEvent)
			{if(client) client->sendChannelEvent(channelId, playerName, channelEvent);}
		void sendCreatureAppear(const Creature* creature, const Position& pos, bool isLogin)
			{if(client) client->sendAddCreature(creature, pos, creature->getTile()->getClientIndexOfThing(this, creature), isLogin);}
		void sendCreatureDisappear(const Creature* creature, uint32_t stackpos, bool isLogout)
			{if(client) client->sendRemoveCreature(creature, creature->getPosition(), stackpos, isLogout);}
		void sendCreatureMove(const Creature* creature, const Tile* newTile, const Position& newPos,
		const Tile* oldTile, const Position& oldPos, uint32_t oldStackPos, bool teleport)
			{if(client) client->sendMoveCreature(creature, newTile, newPos, newTile->getClientIndexOfThing(this, creature), oldTile, oldPos, oldStackPos, teleport);}

		void sendCreatureTurn(const Creature* creature)
			{if(client) client->sendCreatureTurn(creature, creature->getTile()->getClientIndexOfThing(this, creature));}
		void sendCreatureSay(const Creature* creature, SpeakClasses type, const std::string& text, Position* pos = NULL)
			{if(client) client->sendCreatureSay(creature, type, text, pos);}
		void sendCreatureSquare(const Creature* creature, SquareColor_t color)
			{if(client) client->sendCreatureSquare(creature, color);}
		void sendCreatureChangeOutfit(const Creature* creature, const Outfit_t& outfit)
			{if(client) client->sendCreatureOutfit(creature, outfit);}
		void sendCreatureChangeVisible(const Creature* creature, bool visible)
		{
			if(client)
			{
				if(visible)
					client->sendCreatureOutfit(creature, creature->getCurrentOutfit());
				else
					client->sendCreatureInvisible(creature);
			}
		}
		void sendCreatureLight(const Creature* creature)
			{if(client) client->sendCreatureLight(creature);}
		void sendCreatureWalkthrough(const Creature* creature, bool walkthrough)
			{if(client) client->sendCreatureWalkthrough(creature, walkthrough);}
		void sendCreatureShield(const Creature* creature)
			{if(client) client->sendCreatureShield(creature);}
		void sendSpellCooldown(uint8_t spellId, uint32_t time)
			{if(client) client->sendSpellCooldown(spellId, time);}
		void sendSpellGroupCooldown(SpellGroup_t groupId, uint32_t time)
			{if(client) client->sendSpellGroupCooldown(groupId, time);}

		void sendDamageMessage(MessageClasses mclass, const std::string& message, const Position& pos,
			uint32_t primaryDamage = 0, TextColor_t primaryColor = TEXTCOLOR_NONE,
			uint32_t secondaryDamage = 0, TextColor_t secondaryColor = TEXTCOLOR_NONE)
			{if(client) client->sendDamageMessage(mclass, message, pos, primaryDamage, primaryColor, secondaryDamage, secondaryColor);}
		void sendHealMessage(MessageClasses mclass, const std::string& message, const Position& pos, uint32_t heal, TextColor_t color)
			{if(client) client->sendHealMessage(mclass, message, pos, heal, color);}
		void sendExperienceMessage(MessageClasses mclass, const std::string& message, const Position& pos, uint32_t exp, TextColor_t color)
			{if(client) client->sendExperienceMessage(mclass, message, pos, exp, color);}
		void sendModalWindow(const ModalWindow& modalWindow);

		//container
		void sendAddContainerItem(const Container* container, const Item* item);
		void sendUpdateContainerItem(const Container* container, uint8_t slot, const Item* oldItem, const Item* newItem);
		void sendRemoveContainerItem(const Container* container, uint8_t slot, const Item* lastItem);
		void sendContainer(uint32_t cid, const Container* container, bool hasParent)
			{if(client) client->sendContainer(cid, container, hasParent); }

		//inventory
		void sendInventoryItem(slots_t slot, const Item* item)
			{if(client) client->sendInventoryItem(slot, item);}

		//event methods
		virtual void onUpdateTileItem(const Tile* tile, const Position& pos, const Item* oldItem,
			const ItemType& oldType, const Item* newItem, const ItemType& newType);
		virtual void onRemoveTileItem(const Tile* tile, const Position& pos, const ItemType& iType,
			const Item* item);

		virtual void onCreatureAppear(const Creature* creature, bool isLogin);
		virtual void onCreatureDisappear(const Creature* creature, uint32_t stackpos, bool isLogout);
		virtual void onCreatureMove(const Creature* creature, const Tile* newTile, const Position& newPos,
			const Tile* oldTile, const Position& oldPos, bool teleport);

		virtual void onAttackedCreatureDisappear(bool isLogout);
		virtual void onFollowCreatureDisappear(bool isLogout);

		//container
		void onAddContainerItem(const Container* container, const Item* item);
		void onUpdateContainerItem(const Container* container, uint8_t slot,
			const Item* oldItem, const ItemType& oldType, const Item* newItem, const ItemType& newType);
		void onRemoveContainerItem(const Container* container, uint8_t slot, const Item* item);

		void onCloseContainer(const Container* container);
		void onSendContainer(const Container* container);
		void autoCloseContainers(const Container* container);

		//inventory
		void onAddInventoryItem(slots_t slot, Item* item);
		void onUpdateInventoryItem(slots_t slot, Item* oldItem, const ItemType& oldType,
			Item* newItem, const ItemType& newType);
		void onRemoveInventoryItem(slots_t slot, Item* item);

		void sendCancel(const std::string& msg) const
			{if(client) client->sendCancel(msg);}
		void sendCancelMessage(ReturnValue message) const;
		void sendCancelTarget() const
			{if(client) client->sendCancelTarget();}
		void sendCancelWalk() const
			{if(client) client->sendCancelWalk();}
		void sendChangeSpeed(const Creature* creature, uint32_t newSpeed) const
			{if(client) client->sendChangeSpeed(creature, newSpeed);}
		void sendCreatureHealth(const Creature* creature) const
			{if(client) client->sendCreatureHealth(creature);}
		void sendDistanceShoot(const Position& from, const Position& to, unsigned char type) const
			{if(client) client->sendDistanceShoot(from, to, type);}
		void sendHouseWindow(House* house, uint32_t listId) const;
		void sendCreatePrivateChannel(uint16_t channelId, const std::string& channelName)
			{if(client) client->sendCreatePrivateChannel(channelId, channelName);}
		void sendClosePrivate(uint16_t channelId) const
			{if(client) client->sendClosePrivate(channelId);}
		void sendIcons() const
			{if(client) client->sendIcons(getClientIcons());}
		void sendMagicEffect(const Position& pos, uint8_t type) const
			{if(client) client->sendMagicEffect(pos, type);}
		void sendPing();
		void sendPingBack() const
			{if(client) client->sendPingBack();}
		void sendStats();
		void sendBasicData() const
			{if(client) client->sendBasicData();}
		void sendSkills() const
			{if(client) client->sendSkills();}
		void sendTextMessage(MessageClasses mclass, const std::string& message, Position* pos = NULL, uint32_t value = 0, TextColor_t color = TEXTCOLOR_NONE) const
			{if(client) client->sendTextMessage(mclass, message, pos, value, color);}
		void sendReLoginWindow(uint8_t unfairFightReduction) const
			{if(client) client->sendReLoginWindow(unfairFightReduction);}
		void sendTextWindow(Item* item, uint16_t maxlen, bool canWrite) const
			{if(client) client->sendTextWindow(windowTextId, item, maxlen, canWrite);}
		void sendTextWindow(uint32_t itemId, const std::string& text) const
			{if(client) client->sendTextWindow(windowTextId, itemId, text);}
		void sendToChannel(Creature* creature, SpeakClasses type, const std::string& text, uint16_t channelId) const
			{if(client) client->sendToChannel(creature, type, text, channelId);}
		void sendShop(Npc* npc) const
			{if(client) client->sendShop(npc, shopItemList);}
		void sendSaleItemList() const
			{if(client) client->sendSaleItemList(shopItemList);}
		void sendCloseShop() const
			{if(client) client->sendCloseShop();}
		void sendMarketEnter(uint32_t depotId) const
			{if(client) client->sendMarketEnter(depotId);}
		void sendMarketLeave()
			{marketDepotId = -1; if(client) client->sendMarketLeave();}
		void sendMarketBrowseItem(uint16_t itemId, const MarketOfferList& buyOffers, const MarketOfferList& sellOffers) const
			{if(client) client->sendMarketBrowseItem(itemId, buyOffers, sellOffers);}
		void sendMarketBrowseOwnOffers(const MarketOfferList& buyOffers, const MarketOfferList& sellOffers) const
			{if(client) client->sendMarketBrowseOwnOffers(buyOffers, sellOffers);}
		void sendMarketBrowseOwnHistory(const HistoryMarketOfferList& buyOffers, const HistoryMarketOfferList& sellOffers) const
			{if(client) client->sendMarketBrowseOwnHistory(buyOffers, sellOffers);}
		void sendMarketDetail(uint16_t itemId) const
			{if(client) client->sendMarketDetail(itemId);}
		void sendMarketAcceptOffer(MarketOfferEx offer) const
			{if(client) client->sendMarketAcceptOffer(offer);}
		void sendMarketCancelOffer(MarketOfferEx offer) const
			{if(client) client->sendMarketCancelOffer(offer);}
		void sendTradeItemRequest(const Player* player, const Item* item, bool ack) const
			{if(client) client->sendTradeItemRequest(player, item, ack);}
		void sendTradeClose() const
			{if(client) client->sendCloseTrade();}
		void sendWorldLight(LightInfo& lightInfo)
			{if(client) client->sendWorldLight(lightInfo);}
		void sendChannelsDialog()
			{if(client) client->sendChannelsDialog();}
		void sendOpenPrivateChannel(const std::string& receiver)
			{if(client) client->sendOpenPrivateChannel(receiver);}
		void sendOutfitWindow()
			{if(client) client->sendOutfitWindow();}
		void sendCloseContainer(uint32_t cid)
			{if(client) client->sendCloseContainer(cid);}
		void sendChannel(uint16_t channelId, const std::string& channelName)
			{if(client) client->sendChannel(channelId, channelName);}
		void sendTutorial(uint8_t tutorialId)
			{if(client) client->sendTutorial(tutorialId);}
		void sendAddMarker(const Position& pos, uint8_t markType, const std::string& desc)
			{if(client) client->sendAddMarker(pos, markType, desc);}
		void sendQuestLog()
			{if(client) client->sendQuestLog();}
		void sendQuestLine(const Quest* quest)
			{if(client) client->sendQuestLine(quest);}
		void sendEnterWorld()
			{if(client) client->sendEnterWorld();}

		void receivePing() {lastPong = OTSYS_TIME();}

		virtual void onThink(uint32_t interval);
		virtual void onAttacking(uint32_t interval);

		virtual void postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t link = LINK_OWNER);
		virtual void postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, bool isCompleteRemoval, cylinderlink_t link = LINK_OWNER);

		void setNextAction(int64_t time) {if(time > nextAction) {nextAction = time;}}
		bool canDoAction() const {return nextAction <= OTSYS_TIME();}
		uint32_t getNextActionTime() const;

		Item* getWriteItem(uint32_t& _windowTextId, uint16_t& _maxWriteLen);
		void setWriteItem(Item* item, uint16_t _maxWriteLen = 0);

		House* getEditHouse(uint32_t& _windowTextId, uint32_t& _listId);
		void setEditHouse(House* house, uint32_t listId = 0);

		void learnInstantSpell(const std::string& name);
		bool hasLearnedInstantSpell(const std::string& name) const;

		VIPListSet VIPList;
		uint32_t maxVipLimit;

		InvitedToGuildsList invitedToGuildsList;
		GuildWarList guildWarList;

		//items
		ContainerVector containerVec;

		//depots
		DepotMap depotChests;
		DepotLockerMap depotLockerMap;
		uint32_t maxDepotLimit;

	protected:
		void checkTradeState(const Item* item);
		bool hasCapacity(const Item* item, uint32_t count) const;

		void gainExperience(uint64_t exp);
		void addExperience(uint64_t exp, bool useMult = false, bool sendText = false, bool applyStaminaChange = false);

		void updateInventoryWeight();
		void postUpdateGoods(uint32_t itemId);

		void setNextWalkActionTask(SchedulerTask* task);
		void setNextWalkTask(SchedulerTask* task);
		void setNextActionTask(SchedulerTask* task);

		void death();
		virtual bool dropCorpse();
		virtual Item* getCorpse();

		//cylinder implementations
		virtual ReturnValue __queryAdd(int32_t index, const Thing* thing, uint32_t count,
			uint32_t flags, Creature* actor = NULL) const;
		virtual ReturnValue __queryMaxCount(int32_t index, const Thing* thing, uint32_t count, uint32_t& maxQueryCount,
			uint32_t flags) const;
		virtual ReturnValue __queryRemove(const Thing* thing, uint32_t count, uint32_t flags) const;
		virtual Cylinder* __queryDestination(int32_t& index, const Thing* thing, Item** destItem,
			uint32_t& flags);

		virtual void __addThing(Thing* thing);
		virtual void __addThing(int32_t index, Thing* thing);

		virtual void __updateThing(Thing* thing, uint16_t itemId, uint32_t count);
		virtual void __replaceThing(uint32_t index, Thing* thing);

		virtual void __removeThing(Thing* thing, uint32_t count);

		virtual int32_t __getIndexOfThing(const Thing* thing) const;
		virtual int32_t __getFirstIndex() const;
		virtual int32_t __getLastIndex() const;
		virtual uint32_t __getItemTypeCount(uint16_t itemId, int32_t subType = -1) const;
		virtual std::map<uint32_t, uint32_t>& __getAllItemTypeCount(std::map<uint32_t, uint32_t>& countMap) const;
		virtual Thing* __getThing(uint32_t index) const;

		virtual void __internalAddThing(Thing* thing);
		virtual void __internalAddThing(uint32_t index, Thing* thing);

		ProtocolGame* client;

		Party* party;
		PartyList invitePartyList;

		uint32_t level;
		uint32_t levelPercent;
		uint32_t magLevel;
		uint32_t magLevelPercent;
		bool accessLevel;
		AccountType_t accountType;
		int32_t premiumDays;
		uint64_t experience;
		uint32_t damageImmunities;
		uint32_t conditionImmunities;
		uint32_t conditionSuppressions;
		uint32_t condition;
		uint64_t manaSpent;
		int32_t vocationId;
		Vocation* vocation;
		PlayerSex_t sex;
		int32_t soul, soulMax;
		uint64_t groupFlags;
		int16_t blessings;
		uint32_t MessageBufferTicks;
		int32_t MessageBufferCount;
		uint32_t actionTaskEvent;
		uint32_t nextStepEvent;
		uint32_t walkTaskEvent;
		SchedulerTask* walkTask;

		std::string groupName;
		int32_t idleTime;
		int32_t groupId;
		OperatingSystem_t operatingSystem;
		uint16_t protocolVersion;
		bool ghostMode;
		bool depotChange;

		std::list<uint32_t> modalWindows;

		int32_t offlineTrainingSkill;
		int32_t offlineTrainingTime;

		AccountManager* accountManager;

		int16_t marketDepotId;
		int16_t lastDepotId;

		bool mayNotMove;
		bool requestedOutfit;

		double inventoryWeight;
		double capacity;

		int64_t lastPing;
		int64_t lastPong;

		int64_t nextAction;

		bool pzLocked;
		bool isConnecting;
		int32_t bloodHitCount;
		int32_t shieldBlockCount;
		BlockType_t lastAttackBlockType;
		bool addAttackSkillPoint;
		uint64_t lastAttack;
		int32_t shootRange;

		chaseMode_t chaseMode;
		fightMode_t fightMode;
		secureMode_t secureMode;

		time_t lastLoginSaved;
		time_t lastLogout;
		Position loginPosition;
		uint32_t lastIP;

		//account variables
		uint32_t accountNumber;
		std::string password;

		//inventory variables
		Item* inventory[SLOT_LAST];
		bool inventoryAbilities[SLOT_LAST];

		//player advances variables
		uint32_t skills[SKILL_LAST + 1][3];

		//extra skill modifiers
		int32_t varSkills[SKILL_LAST + 1];

		//extra stat modifiers
		int32_t varStats[STAT_LAST + 1];

		LearnedInstantSpellList learnedInstantSpellList;
		ConditionList storedConditionList;

		//trade variables
		Player* tradePartner;
		tradestate_t tradeState;
		Item* tradeItem;

		//shop variables
		Npc* shopOwner;
		int32_t purchaseCallback;
		int32_t saleCallback;
		std::list<ShopInfo> shopItemList;

		std::map<uint32_t, uint32_t> goodsMap;

		Inbox* inbox;

		std::string name;
		std::string nameDescription;
		uint32_t guid;

		uint32_t town;

		uint64_t bankBalance;

		uint16_t lastStatsTrainingTime;

		Position lastWalkthroughPosition;
		int64_t lastWalkthroughAttempt;
		int64_t lastToggleMount;

		//guild variables
		uint32_t guildId;
		std::string guildName;
		std::string guildRank;
		std::string guildNick;
		int8_t guildLevel;

		StorageMap storageMap;
		int64_t lastQuestlogUpdate;

		LightInfo itemsLight;

		OutfitList m_playerOutfits;

		BedItem* bedItem;

		//stamina
		uint16_t staminaMinutes;
		time_t nextUseStaminaTime;

		//read/write storage data
		uint32_t windowTextId;
		Item* writeItem;
		uint16_t maxWriteLen;
		House* editHouse;
		uint32_t editListId;

		int64_t skullTicks;
		Skulls_t skull;
		typedef OTSERV_HASH_SET<uint32_t> AttackedSet;
		AttackedSet attackedSet;

		void updateItemsLight(bool internal = false);
		virtual int32_t getStepSpeed() const
		{
			if(getSpeed() > PLAYER_MAX_SPEED)
				return PLAYER_MAX_SPEED;
			else if(getSpeed() < PLAYER_MIN_SPEED)
				return PLAYER_MIN_SPEED;

			return getSpeed();
		}
		void updateBaseSpeed()
		{
			if(!hasFlag(PlayerFlag_SetMaxSpeed))
				baseSpeed = vocation->getBaseSpeed() + (2 * (level - 1));
			else
				baseSpeed = PLAYER_MAX_SPEED;
		}

		bool isPromoted() const;

		uint32_t getAttackSpeed() const {return vocation->getAttackSpeed();}

		uint16_t getDropPercent() const;

		static uint32_t getPercentLevel(uint64_t count, uint64_t nextLevelCount);
		double getLostPercent() const;
		virtual uint64_t getLostExperience() const {return skillLoss ? uint64_t(experience * getLostPercent()) : 0;}
		virtual void dropLoot(Container* corpse);
		virtual uint32_t getDamageImmunities() const { return damageImmunities; }
		virtual uint32_t getConditionImmunities() const { return conditionImmunities; }
		virtual uint32_t getConditionSuppressions() const { return conditionSuppressions; }
		virtual uint16_t getLookCorpse() const;
		virtual void getPathSearchParams(const Creature* creature, FindPathParams& fpp) const;

	friend class Game;
	friend class Npc;
	friend class LuaScriptInterface;
	friend class Commands;
	friend class Map;
	friend class Actions;
	friend class IOLoginData;
	friend class ProtocolGame;
};

#endif
