////////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////
#include "otpch.h"
#include <iostream>
#include <iomanip>

#include "item.h"
#include "container.h"
#include "depot.h"

#include "teleport.h"
#include "trashholder.h"
#include "mailbox.h"

#include "luascript.h"
#include "combat.h"

#include "house.h"
#include "beds.h"

#include "actions.h"
#include "configmanager.h"
#include "game.h"

extern Game g_game;
extern ConfigManager g_config;

Items Item::items;
Item* Item::CreateItem(const uint16_t _type, uint16_t _count/* = 1*/)
{
	const ItemType& it = Item::items[_type];
	if(it.group == ITEM_GROUP_DEPRECATED)
	{
		#ifdef __DEBUG__
		std::cout << "Error: [Item::CreateItem] Item id " << it.id << " has been declared deprecated." << std::endl;
		#endif
		return NULL;
	}

	if(!it.id)
		return NULL;

	Item* newItem = NULL;
	if(it.isDepot())
		newItem = new Depot(_type);
	else if(it.isContainer())
		newItem = new Container(_type);
	else if(it.isTeleport())
		newItem = new Teleport(_type);
	else if(it.isMagicField())
		newItem = new MagicField(_type);
	else if(it.isDoor())
		newItem = new Door(_type);
	else if(it.isTrashHolder())
		newItem = new TrashHolder(_type, it.magicEffect);
	else if(it.isMailbox())
		newItem = new Mailbox(_type);
	else if(it.isBed())
		newItem = new BedItem(_type);
	else if(it.id >= 2210 && it.id <= 2212)
		newItem = new Item(_type - 3, _count);
	else if(it.id == 2215 || it.id == 2216)
		newItem = new Item(_type - 2, _count);
	else if(it.id >= 2202 && it.id <= 2206)
		newItem = new Item(_type - 37, _count);
	else if(it.id == 2640)
		newItem = new Item(6132, _count);
	else if(it.id == 6301)
		newItem = new Item(6300, _count);
	else
		newItem = new Item(_type, _count);

	newItem->useThing2();
	return newItem;
}

Item* Item::CreateItem(PropStream& propStream)
{
	uint16_t _id;
	if(!propStream.GET_USHORT(_id))
		return NULL;

	return Item::CreateItem(items.getRandomizedItem(_id), 0);
}

bool Item::loadItem(xmlNodePtr node, Container* parent)
{
	if(xmlStrcmp(node->name, (const xmlChar*)"item"))
		return false;

	int32_t intValue;
	std::string strValue;

	Item* item = NULL;
	if(readXMLInteger(node, "id", intValue))
		item = Item::CreateItem(intValue);

	if(!item)
		return false;

	//optional
	if(readXMLInteger(node, "subtype", intValue) || readXMLInteger(node, "subType", intValue))
		item->setSubType(intValue);

	if(readXMLInteger(node, "actionId", intValue) || readXMLInteger(node, "actionid", intValue)
		|| readXMLInteger(node, "aid", intValue))
		item->setActionId(intValue);

	if(readXMLInteger(node, "uniqueId", intValue) || readXMLInteger(node, "uniqueid", intValue)
		|| readXMLInteger(node, "uid", intValue))
		item->setUniqueId(intValue);

	if(readXMLString(node, "text", strValue))
		item->setText(strValue);

	//TODO: more optionals?
	if(item->getContainer())
		loadContainer(node, item->getContainer());

	if(parent)
		parent->addItem(item);

	return true;
}

bool Item::loadContainer(xmlNodePtr parentNode, Container* parent)
{
	xmlNodePtr node = parentNode->children;
	while(node)
	{
		if(node->type != XML_ELEMENT_NODE)
		{
			node = node->next;
			continue;
		}

		if(!xmlStrcmp(node->name, (const xmlChar*)"item") && !loadItem(node, parent))
			return false;

		node = node->next;
	}

	return true;
}

Item::Item(const uint16_t _type, uint16_t _count/* = 0*/):
	ItemAttributes()
{
	id = _type;
	count = 1;
	raid = NULL;

	const ItemType& it = items[id];
	if(it.charges)
		setCharges(it.charges);

	if(it.isFluidContainer() || it.isSplash())
		setFluidType(_count);
	else if(it.stackable && _count)
		count = _count;
	else if(it.charges && _count)
		setCharges(_count);

	loadedFromMap = false;
	setDefaultDuration();
}

Item::Item(const Item& i):
	Thing(), ItemAttributes()
{
	id = i.id;
	count = i.count;
	raid = i.raid;

	m_attributes = i.m_attributes;
	if(i.m_firstAttr)
		m_firstAttr = new Attribute(*i.m_firstAttr);
}

Item* Item::clone() const
{
	Item* tmp = Item::CreateItem(id, count);
	tmp->m_attributes = m_attributes;
	if(m_firstAttr)
		tmp->m_firstAttr = new Attribute(*m_firstAttr);

	return tmp;
}

void Item::copyAttributes(Item* item)
{
	m_attributes = item->m_attributes;
	if(item->m_firstAttr)
		m_firstAttr = new Attribute(*item->m_firstAttr);

	removeAttribute(ATTR_ITEM_DECAYING);
	removeAttribute(ATTR_ITEM_DURATION);
}

void Item::onRemoved()
{
	if(raid)
	{
		raid->unRef();
		raid = NULL;
	}

	if(getUniqueId() != 0)
		ScriptEnviroment::removeUniqueThing(this);
}

void Item::setDefaultSubtype()
{
	count = 1;
	const ItemType& it = items[id];
	if(it.charges)
		setCharges(it.charges);
}

void Item::setID(uint16_t newid)
{
	const ItemType& prevIt = Item::items[id];
	id = newid;

	const ItemType& it = Item::items[newid];
	uint32_t newDuration = it.decayTime * 1000;

	if(newDuration == 0 && !it.stopTime && it.decayTo == -1)
	{
		removeAttribute(ATTR_ITEM_DECAYING);
		removeAttribute(ATTR_ITEM_DURATION);
	}

	if(hasAttribute(ATTR_ITEM_CORPSEOWNER))
		removeAttribute(ATTR_ITEM_CORPSEOWNER);

	if(newDuration > 0 && (!prevIt.stopTime || !hasAttribute(ATTR_ITEM_DURATION)))
	{
		setDecaying(DECAYING_FALSE);
		setDuration(newDuration);
	}
}

bool Item::floorChange(FloorChange_t change/* = CHANGE_NONE*/) const
{
	if(change < CHANGE_NONE)
		return Item::items[id].floorChange[change];

	for(int32_t i = CHANGE_PRE_FIRST; i < CHANGE_LAST; ++i)
	{
		if(Item::items[id].floorChange[i])
			return true;
	}

	return false;
}

Player* Item::getHoldingPlayer()
{
	Cylinder* p = getParent();
	while(p)
	{
		if(p->getCreature())
			return p->getCreature()->getPlayer();

		p = p->getParent();
	}

	return NULL;
}

const Player* Item::getHoldingPlayer() const
{
	return const_cast<Item*>(this)->getHoldingPlayer();
}

uint16_t Item::getSubType() const
{
	const ItemType& it = items[getID()];
	if(it.isFluidContainer() || it.isSplash())
		return getFluidType();

	if(it.charges)
		return getCharges();

	return count;
}

void Item::setSubType(uint16_t n)
{
	const ItemType& it = items[id];
	if(it.isFluidContainer() || it.isSplash())
		setFluidType(n);
	else if(it.charges)
		setCharges(n);
	else
		count = n;
}

Attr_ReadValue Item::readAttr(AttrTypes_t attr, PropStream& propStream)
{
	switch(attr)
	{
		case ATTR_COUNT:
		{
			uint8_t _count = 0;
			if(!propStream.GET_UCHAR(_count))
				return ATTR_READ_ERROR;

			setSubType(_count);
			break;
		}

		case ATTR_ACTION_ID:
		{
			uint16_t _actionid = 0;
			if(!propStream.GET_USHORT(_actionid))
				return ATTR_READ_ERROR;

			setActionId(_actionid);
			break;
		}

		case ATTR_UNIQUE_ID:
		{
			uint16_t _uniqueid;
			if(!propStream.GET_USHORT(_uniqueid))
				return ATTR_READ_ERROR;

			setUniqueId(_uniqueid);
			break;
		}

		case ATTR_NAME:
		{
			std::string _name;
			if(!propStream.GET_STRING(_name))
				return ATTR_READ_ERROR;

			setName(_name);
			break;
		}

		case ATTR_PLURALNAME:
		{
			std::string _pluralname;
			if(!propStream.GET_STRING(_pluralname))
				return ATTR_READ_ERROR;

			setPluralName(_pluralname);
			break;
		}

		case ATTR_ARTICLE:
		{
			std::string _article;
			if(!propStream.GET_STRING(_article))
				return ATTR_READ_ERROR;

			setArticle(_article);
			break;
		}

		case ATTR_ATTACK:
		{
			int32_t _attack;
			if(!propStream.GET_ULONG((uint32_t&)_attack))
				return ATTR_READ_ERROR;

			setAttack(_attack);
			break;
		}

		case ATTR_EXTRAATTACK:
		{
			int32_t _extraattack;
			if(!propStream.GET_ULONG((uint32_t&)_extraattack))
				return ATTR_READ_ERROR;

			setExtraAttack(_extraattack);
			break;
		}

		case ATTR_DEFENSE:
		{
			int32_t _defense;
			if(!propStream.GET_ULONG((uint32_t&)_defense))
				return ATTR_READ_ERROR;

			setDefense(_defense);
			break;
		}

		case ATTR_EXTRADEFENSE:
		{
			int32_t _extradefense;
			if(!propStream.GET_ULONG((uint32_t&)_extradefense))
				return ATTR_READ_ERROR;

			setExtraDefense(_extradefense);
			break;
		}

		case ATTR_ARMOR:
		{
			int32_t _armor;
			if(!propStream.GET_ULONG((uint32_t&)_armor))
				return ATTR_READ_ERROR;

			setArmor(_armor);
			break;
		}

		case ATTR_ATTACKSPEED:
		{
			int32_t _attackspeed;
			if(!propStream.GET_ULONG((uint32_t&)_attackspeed))
				return ATTR_READ_ERROR;

			setAttackSpeed(_attackspeed);
			break;
		}

		case ATTR_HITCHANCE:
		{
			int32_t _hitchance;
			if(!propStream.GET_ULONG((uint32_t&)_hitchance))
				return ATTR_READ_ERROR;

			setHitChance(_hitchance);
			break;
		}

		case ATTR_SCRIPTPROTECTED:
		{
			uint8_t _scriptProtected = 0;
			if(!propStream.GET_UCHAR(_scriptProtected))
				return ATTR_READ_ERROR;

			setScriptProtected(_scriptProtected);
			break;
		}

		case ATTR_TEXT:
		{
			std::string _text;
			if(!propStream.GET_STRING(_text))
				return ATTR_READ_ERROR;

			setText(_text);
			break;
		}

		case ATTR_WRITTENDATE:
		{
			uint32_t _writtenDate;
			if(!propStream.GET_ULONG(_writtenDate))
				return ATTR_READ_ERROR;

			setDate(_writtenDate);
			break;
		}

		case ATTR_WRITTENBY:
		{
			std::string _writer;
			if(!propStream.GET_STRING(_writer))
				return ATTR_READ_ERROR;

			setWriter(_writer);
			break;
		}

		case ATTR_DESC:
		{
			std::string _text;
			if(!propStream.GET_STRING(_text))
				return ATTR_READ_ERROR;

			setSpecialDescription(_text);
			break;
		}

		case ATTR_RUNE_CHARGES:
		{
			uint8_t _charges = 1;
			if(!propStream.GET_UCHAR(_charges))
				return ATTR_READ_ERROR;

			setSubType((uint16_t)_charges);
			break;
		}

		case ATTR_CHARGES:
		{
			uint16_t _charges = 1;
			if(!propStream.GET_USHORT(_charges))
				return ATTR_READ_ERROR;

			setSubType(_charges);
			break;
		}

		case ATTR_DURATION:
		{
			uint32_t duration = 0;
			if(!propStream.GET_ULONG(duration))
				return ATTR_READ_ERROR;

			setDuration(std::max((uint32_t)0, duration));
			break;
		}

		case ATTR_DECAYING_STATE:
		{
			uint8_t state = 0;
			if(!propStream.GET_UCHAR(state))
				return ATTR_READ_ERROR;

			if(state != DECAYING_FALSE)
				setDecaying(DECAYING_PENDING);

			break;
		}

		//these should be handled through derived classes
		//if these are called then something has changed in the items.otb since the map was saved
		//just read the values

		//Depot class
		case ATTR_DEPOT_ID:
		{
			uint16_t _depotId;
			if(!propStream.GET_USHORT(_depotId))
				return ATTR_READ_ERROR;

			return ATTR_READ_CONTINUE;
		}

		//Door class
		case ATTR_HOUSEDOORID:
		{
			uint8_t _doorId;
			if(!propStream.GET_UCHAR(_doorId))
				return ATTR_READ_ERROR;

			return ATTR_READ_CONTINUE;
		}

		//Teleport class
		case ATTR_TELE_DEST:
		{
			TeleportDest* _teleDest;
			if(!propStream.GET_STRUCT(_teleDest))
				return ATTR_READ_ERROR;

			return ATTR_READ_CONTINUE;
		}

		//Bed class
		case ATTR_SLEEPERGUID:
		{
			uint32_t _sleeper;
			if(!propStream.GET_ULONG(_sleeper))
				return ATTR_READ_ERROR;

			return ATTR_READ_CONTINUE;
		}

		case ATTR_SLEEPSTART:
		{
			uint32_t _sleepStart;
			if(!propStream.GET_ULONG(_sleepStart))
				return ATTR_READ_ERROR;

			return ATTR_READ_CONTINUE;
		}

		//Container class
		case ATTR_CONTAINER_ITEMS:
		default:
			return ATTR_READ_ERROR;
	}

	return ATTR_READ_CONTINUE;
}

bool Item::unserializeAttr(PropStream& propStream)
{
	uint8_t attrType = 0;
	while(propStream.GET_UCHAR(attrType) && attrType != ATTR_END)
	{
		switch(readAttr((AttrTypes_t)attrType, propStream))
		{
			case ATTR_READ_ERROR:
				return false;

			case ATTR_READ_END:
				return true;

			default:
				break;
		}
	}

	return true;
}

bool Item::serializeAttr(PropWriteStream& propWriteStream) const
{
	if(isStackable() || isFluidContainer() || isSplash())
	{
		propWriteStream.ADD_UCHAR(ATTR_COUNT);
		propWriteStream.ADD_UCHAR(getSubType());
	}

	if(hasCharges())
	{
		propWriteStream.ADD_UCHAR(ATTR_CHARGES);
		propWriteStream.ADD_USHORT(getCharges());
	}

	if(!isNotMoveable())
	{
		if(getActionId())
		{
			propWriteStream.ADD_UCHAR(ATTR_ACTION_ID);
			propWriteStream.ADD_USHORT(getActionId());
		}

		if(getUniqueId())
		{
			propWriteStream.ADD_UCHAR(ATTR_UNIQUE_ID);
			propWriteStream.ADD_USHORT(getUniqueId());
		}
	}

	const std::string& _text = getText();
	if(_text.length() > 0)
	{
		propWriteStream.ADD_UCHAR(ATTR_TEXT);
		propWriteStream.ADD_STRING(_text);
	}

	if(getDate())
	{
		propWriteStream.ADD_UCHAR(ATTR_WRITTENDATE);
		propWriteStream.ADD_ULONG(getDate());
	}

	const std::string& _writer = getWriter();
	if(_writer.length() > 0)
	{
		propWriteStream.ADD_UCHAR(ATTR_WRITTENBY);
		propWriteStream.ADD_STRING(_writer);
	}

	const std::string& _specialDesc = getSpecialDescription();
	if(_specialDesc.length() > 0)
	{
		propWriteStream.ADD_UCHAR(ATTR_DESC);
		propWriteStream.ADD_STRING(_specialDesc);
	}

	if(hasAttribute(ATTR_ITEM_DURATION))
	{
		propWriteStream.ADD_UCHAR(ATTR_DURATION);
		propWriteStream.ADD_ULONG(getDuration());
	}

	uint32_t decayState = getDecaying();
	if(decayState == DECAYING_TRUE || decayState == DECAYING_PENDING)
	{
		propWriteStream.ADD_UCHAR(ATTR_DECAYING_STATE);
		propWriteStream.ADD_UCHAR(decayState);
	}

	if(getStrAttr(ATTR_ITEM_NAME) != "")
	{
		const std::string& _name = getName();
		if(_name.length() > 0)
		{
			propWriteStream.ADD_UCHAR(ATTR_NAME);
			propWriteStream.ADD_STRING(_name);
		}
	}

	if(getStrAttr(ATTR_ITEM_PLURALNAME) != "")
	{
		const std::string& _pluralname = getPluralName();
		if(_pluralname.length() > 0)
		{
			propWriteStream.ADD_UCHAR(ATTR_PLURALNAME);
			propWriteStream.ADD_STRING(_pluralname);
		}
	}

	if(getStrAttr(ATTR_ITEM_ARTICLE) != "")
	{
		const std::string& _article = getArticle();
		if(_article.length() > 0)
		{
			propWriteStream.ADD_UCHAR(ATTR_ARTICLE);
			propWriteStream.ADD_STRING(_article);
		}
	}

	if(hasAttribute(ATTR_ITEM_ATTACK))
	{
		propWriteStream.ADD_UCHAR(ATTR_ATTACK);
		propWriteStream.ADD_ULONG(getAttack());
	}

	if(hasAttribute(ATTR_ITEM_EXTRAATTACK))
	{
		propWriteStream.ADD_UCHAR(ATTR_EXTRAATTACK);
		propWriteStream.ADD_ULONG(getExtraAttack());
	}

	if(hasAttribute(ATTR_ITEM_DEFENSE))
	{
		propWriteStream.ADD_UCHAR(ATTR_DEFENSE);
		propWriteStream.ADD_ULONG(getDefense());
	}

	if(hasAttribute(ATTR_ITEM_EXTRADEFENSE))
	{
		propWriteStream.ADD_UCHAR(ATTR_EXTRADEFENSE);
		propWriteStream.ADD_ULONG(getExtraDefense());
	}

	if(hasAttribute(ATTR_ITEM_ARMOR))
	{
		propWriteStream.ADD_UCHAR(ATTR_ARMOR);
		propWriteStream.ADD_ULONG(getArmor());
	}

	if(hasAttribute(ATTR_ITEM_ATTACKSPEED))
	{
		propWriteStream.ADD_UCHAR(ATTR_ATTACKSPEED);
		propWriteStream.ADD_ULONG(getAttackSpeed());
	}

	if(hasAttribute(ATTR_ITEM_HITCHANCE))
	{
		propWriteStream.ADD_UCHAR(ATTR_HITCHANCE);
		propWriteStream.ADD_ULONG(getHitChance());
	}

	if(hasAttribute(ATTR_ITEM_SCRIPTPROTECTED))
	{
		propWriteStream.ADD_UCHAR(ATTR_SCRIPTPROTECTED);
		propWriteStream.ADD_UCHAR(isScriptProtected() ? 1 : 0);
	}

	return true;
}

bool Item::hasProperty(enum ITEMPROPERTY prop) const
{
	const ItemType& it = items[id];
	switch(prop)
	{
		case BLOCKSOLID:
			if(it.blockSolid)
				return true;
			break;

		case MOVEABLE:
			if(it.moveable && (!isLoadedFromMap() ||
				(getUniqueId() == 0 && (getActionId() == 0 || getContainer()))))
				return true;
			break;

		case HASHEIGHT:
			if(it.hasHeight)
				return true;
			break;

		case BLOCKPROJECTILE:
			if(it.blockProjectile)
				return true;
			break;

		case BLOCKPATH:
			if(it.blockPathFind)
				return true;
			break;

		case ISVERTICAL:
			if(it.isVertical)
				return true;
			break;

		case ISHORIZONTAL:
			if(it.isHorizontal)
				return true;
			break;

		case IMMOVABLEBLOCKSOLID:
			if(it.blockSolid && (!it.moveable || (isLoadedFromMap() &&
				(getUniqueId() || (getActionId() && getContainer())))))
				return true;
			break;

		case IMMOVABLEBLOCKPATH:
			if(it.blockPathFind && (!it.moveable || (isLoadedFromMap() &&
				(getUniqueId() || (getActionId() && getContainer())))))
				return true;
			break;

		case SUPPORTHANGABLE:
			if(it.isHorizontal || it.isVertical)
				return true;
			break;

		case IMMOVABLENOFIELDBLOCKPATH:
			if(!it.isMagicField() && it.blockPathFind && (!it.moveable || (isLoadedFromMap() &&
				(getUniqueId() || (getActionId() && getContainer())))))
				return true;
			break;

		case NOFIELDBLOCKPATH:
			if(!it.isMagicField() && it.blockPathFind)
				return true;
			break;

		default:
			break;
	}

	return false;
}

double Item::getWeight() const
{
	if(isStackable())
		return items[id].weight * std::max((int32_t)1, (int32_t)count);

	return items[id].weight;
}

std::string Item::getDescription(const ItemType& it, int32_t lookDistance, const Item* item/* = NULL*/,
	int32_t subType/* = -1*/, bool addArticle/* = true*/)
{
	std::stringstream s;
	s << getNameDescription(it, item, subType, addArticle);
	if(item)
		subType = item->getSubType();

	bool dot = true;
	if(it.isRune())
	{
		s << "(";
		if(!it.runeSpellName.empty())
			s << "\"" << it.runeSpellName << "\", ";

		s << "Charges:" << subType << ")";
		if(it.runeLevel > 0 || it.runeMagLevel > 0 || (it.vocationString != "" && it.wieldInfo == 0))
		{
			s << "." << std::endl << "It can only be used";
			if(it.vocationString != "" && it.wieldInfo == 0)
				s << " by " << it.vocationString;

			bool begin = true;
			if(it.runeLevel > 0)
			{
				begin = false;
				s << " with level " << it.runeLevel;
			}

			if(it.runeMagLevel > 0)
			{
				begin = false;
				s << " " << (begin ? "with" : "and") << " magic level " << it.runeMagLevel;
			}

			if(!begin)
				s << " or higher";
		}
	}
	else if(it.weaponType != WEAPON_NONE)
	{
		bool begin = true;
		if(it.weaponType == WEAPON_DIST && it.ammoType != AMMO_NONE)
		{
			begin = false;
			s << " (Range:" << int32_t(item ? item->getShootRange() : it.shootRange);
			if(it.attack || it.extraAttack || (item && (item->getAttack() || item->getExtraAttack())))
			{
				s << ", Atk " << std::showpos << int32_t(item ? item->getAttack() : it.attack);
				if(it.extraAttack || (item && item->getExtraAttack()))
					s << " " << std::showpos << int32_t(item ? item->getExtraAttack() : it.extraAttack) << std::noshowpos;
			}

			if(it.hitChance != -1 || (item && item->getHitChance() != -1))
				s << ", Hit% " << std::showpos << (item ? item->getHitChance() : it.hitChance) << std::noshowpos;
		}
		else if(it.weaponType != WEAPON_AMMO && it.weaponType != WEAPON_WAND)
		{
			if(it.attack || it.extraAttack || (item && (item->getAttack() || item->getExtraAttack())))
			{
				begin = false;
				s << " (Atk:";
				if(it.abilities.elementType != COMBAT_NONE && it.decayTo < 1)
				{
					s << std::max((int32_t)0, int32_t((item ? item->getAttack() : it.attack) - it.abilities.elementDamage));
					if(it.extraAttack || (item && item->getExtraAttack()))
						s << " " << std::showpos << int32_t(item ? item->getExtraAttack() : it.extraAttack) << std::noshowpos;

					s << " physical + " << it.abilities.elementDamage << " " << getCombatName(it.abilities.elementType);
				}
				else
				{
					s << int32_t(item ? item->getAttack() : it.attack);
					if(it.extraAttack || (item && item->getExtraAttack()))
						s << " " << std::showpos << int32_t(item ? item->getExtraAttack() : it.extraAttack) << std::noshowpos;
				}
			}

			if(it.defense || it.extraDefense || (item && (item->getDefense() || item->getExtraDefense())))
			{
				if(begin)
				{
					begin = false;
					s << " (";
				}
				else
					s << ", ";

				s << "Def:" << int32_t(item ? item->getDefense() : it.defense);
				if(it.extraDefense || (item && item->getExtraDefense()))
					s << " " << std::showpos << int32_t(item ? item->getExtraDefense() : it.extraDefense) << std::noshowpos;
			}
		}

		for(uint16_t i = SKILL_FIRST; i <= SKILL_LAST; i++)
		{
			if(!it.abilities.skills[i])
				continue;

			if(begin)
			{
				begin = false;
				s << " (";
			}
			else
				s << ", ";

			s << getSkillName(i) << " " << std::showpos << (int32_t)it.abilities.skills[i] << std::noshowpos;
		}

		if(it.abilities.stats[STAT_MAGICLEVEL])
		{
			if(begin)
			{
				begin = false;
				s << " (";
			}
			else
				s << ", ";

			s << "magic level " << std::showpos << (int32_t)it.abilities.stats[STAT_MAGICLEVEL] << std::noshowpos;
		}

		int32_t show = it.abilities.absorb[COMBAT_FIRST];
		for(uint32_t i = (COMBAT_FIRST + 1); i <= COMBAT_LAST; i++)
		{
			if(it.abilities.absorb[i] == show)
				continue;

			show = 0;
			break;
		}

		if(!show)
		{
			bool tmp = true;
			for(uint32_t i = COMBAT_FIRST; i <= COMBAT_LAST; i++)
			{
				if(!it.abilities.absorb[i])
					continue;

				if(tmp)
				{
					if(begin)
					{
						begin = false;
						s << " (";
					}
					else
						s << ", ";

					tmp = false;
					s << "protection ";
				}
				else
					s << ", ";

				s << getCombatName((CombatType_t)i) << " " << std::showpos << it.abilities.absorb[i] << std::noshowpos << "%";
			}
		}
		else
		{
			if(begin)
			{
				begin = false;
				s << " (";
			}
			else
				s << ", ";

			s << "protection all " << std::showpos << show << std::noshowpos << "%";
		}

		if(it.abilities.speed)
		{
			if(begin)
			{
				begin = false;
				s << " (";
			}
			else
				s << ", ";

			s << "speed " << std::showpos << (int32_t)(it.abilities.speed / 2) << std::noshowpos;
		}

		if(!begin)
			s << ")";
	}
	else if(it.armor || (item && item->getArmor()) || it.showAttributes)
	{
		int32_t tmp = it.armor;
		if(item)
			tmp = item->getArmor();

		bool begin = true;
		if(tmp)
		{
			s << " (Arm:" << tmp;
			begin = false;
		}

		for(uint16_t i = SKILL_FIRST; i <= SKILL_LAST; i++)
		{
			if(!it.abilities.skills[i])
				continue;

			if(begin)
			{
				begin = false;
				s << " (";
			}
			else
				s << ", ";

			s << getSkillName(i) << " " << std::showpos << (int32_t)it.abilities.skills[i] << std::noshowpos;
		}

		if(it.abilities.stats[STAT_MAGICLEVEL])
		{
			if(begin)
			{
				begin = false;
				s << " (";
			}
			else
				s << ", ";

			s << "magic level " << std::showpos << (int32_t)it.abilities.stats[STAT_MAGICLEVEL] << std::noshowpos;
		}

		int32_t show = it.abilities.absorb[COMBAT_FIRST];
		for(uint32_t i = (COMBAT_FIRST + 1); i <= COMBAT_LAST; i++)
		{
			if(it.abilities.absorb[i] == show)
				continue;

			show = 0;
			break;
		}

		if(!show)
		{
			bool tmp = true;
			for(uint32_t i = COMBAT_FIRST; i <= COMBAT_LAST; i++)
			{
				if(!it.abilities.absorb[i])
					continue;

				if(tmp)
				{
					tmp = false;
					if(begin)
					{
						begin = false;
						s << " (";
					}
					else
						s << ", ";

					s << "protection ";
				}
				else
					s << ", ";

				s << getCombatName((CombatType_t)i) << " " << std::showpos << it.abilities.absorb[i] << std::noshowpos << "%";
			}
		}
		else
		{
			if(begin)
			{
				begin = false;
				s << " (";
			}
			else
				s << ", ";

			s << "protection all " << std::showpos << show << std::noshowpos << "%";
		}

		if(it.abilities.speed)
		{
			if(begin)
			{
				begin = false;
				s << " (";
			}
			else
				s << ", ";

			s << "speed " << std::showpos << (int32_t)(it.abilities.speed / 2) << std::noshowpos;
		}

		if(!begin)
			s << ")";
	}
	else if(it.isContainer())
		s << " (Vol:" << (int32_t)it.maxItems << ")";
	else if(it.isKey())
		s << " (Key:" << (item ? (int32_t)item->getActionId() : 0) << ")";
	else if(it.isFluidContainer())
	{
		if(subType > 0)
			s << " of " << (items[subType].name.length() ? items[subType].name : "unknown");
		else
			s << ". It is empty";
	}
	else if(it.isSplash())
	{
		s << " of ";
		if(subType > 0 && items[subType].name.length())
			s << items[subType].name;
		else
			s << "unknown";
	}
	else if(it.allowDistRead)
	{
		s << std::endl;
		if(item && !item->getText().empty())
		{
			if(lookDistance <= 4)
			{
				if(!item->getWriter().empty())
				{
					s << item->getWriter() << " wrote";
					time_t date = item->getDate();
					if(date > 0)
						s << " on " << formatDate(date);

					s << ": ";
				}
				else
					s << "You read: ";

				std::string text = item->getText();
				s << text;
				if(!text.empty())
				{
					char end = *text.rbegin();
					if(end == '?' || end == '!' || end == '.')
						dot = false;
				}
			}
			else
				s << "You are too far away to read it";
		}
		else
			s << "Nothing is written on it";
	}
	else if(it.levelDoor && item && item->getActionId() >= it.levelDoor &&
		item->getActionId() <= (it.levelDoor + g_config.getNumber(ConfigManager::MAXIMUM_DOOR_LEVEL)))
		s << " for level " << item->getActionId() - it.levelDoor;

	if(it.showCharges)
		s << " that has " << subType << " charge" << (subType != 1 ? "s" : "") << " left";

	if(it.showDuration)
	{
		if(item && item->hasAttribute(ATTR_ITEM_DURATION))
		{
			int32_t duration = item->getDuration() / 1000;
			s << " that has energy for ";

			if(duration >= 120)
				s << duration / 60 << " minutes left";
			else if(duration > 60)
				s << "1 minute left";
			else
				s << " less than a minute left";
		}
		else
			s << " that is brand-new";
	}

	if(dot)
		s << ".";

	if(it.wieldInfo)
	{
		s << std::endl << "It can only be wielded properly by ";
		if(it.wieldInfo & WIELDINFO_PREMIUM)
			s << "premium ";

		if(it.wieldInfo & WIELDINFO_VOCREQ)
			s << it.vocationString;
		else
			s << "players";

		if(it.wieldInfo & WIELDINFO_LEVEL)
			s << " of level " << (int32_t)it.minReqLevel << " or higher";

		if(it.wieldInfo & WIELDINFO_MAGLV)
		{
			if(it.wieldInfo & WIELDINFO_LEVEL)
				s << " and";
			else
				s << " of";

			s << " magic level " << (int32_t)it.minReqMagicLevel << " or higher";
		}

		s << ".";
	}

	if(lookDistance <= 1 && it.pickupable)
	{
		s << std::endl;
		if(!item)
			s << getWeightDescription(it.weight, it.stackable, subType);
		else
			s << item->getWeightDescription();
	}

	if(it.abilities.elementType != COMBAT_NONE && it.decayTo > 0)
	{
		s << std::endl << "It is temporarily enchanted with " << getCombatName(it.abilities.elementType) << " (";
		s << std::max((int32_t)0, int32_t((item ? item->getAttack() : it.attack) - it.abilities.elementDamage));
		if(it.extraAttack || (item && item->getExtraAttack()))
			s << " " << std::showpos << int32_t(item ? item->getExtraAttack() : it.extraAttack) << std::noshowpos;

		s << " physical + " << it.abilities.elementDamage << " " << getCombatName(it.abilities.elementType) << " damage).";
	}

	std::string str;
	if(item && !item->getSpecialDescription().empty())
		str = item->getSpecialDescription();
	else if(!it.description.empty() && lookDistance <= 1)
		str = it.description;

	if(str.empty())
		return s.str();

	if(str.find("|PLAYERNAME|") != std::string::npos)
	{
		std::string tmp = "You";
		if(item)
		{
			if(const Player* player = item->getHoldingPlayer())
				tmp = player->getName();
		}

		replaceString(str, "|PLAYERNAME|", tmp);
	}

	if(str.find("|TIME|") != std::string::npos || str.find("|DATE|") != std::string::npos || str.find(
		"|DAY|") != std::string::npos || str.find("|MONTH|") != std::string::npos || str.find(
		"|YEAR|") != std::string::npos || str.find("|HOUR|") != std::string::npos || str.find(
		"|MINUTES|") != std::string::npos || str.find("|SECONDS|") != std::string::npos ||
		str.find("|WEEKDAY|") != std::string::npos || str.find("|YEARDAY|") != std::string::npos)
	{
		time_t now = time(NULL);
		tm* ts = localtime(&now);

		std::stringstream ss;
		ss << ts->tm_sec;
		replaceString(str, "|SECONDS|", ss.str());

		ss.str("");
		ss << ts->tm_min;
		replaceString(str, "|MINUTES|", ss.str());

		ss.str("");
		ss << ts->tm_hour;
		replaceString(str, "|HOUR|", ss.str());

		ss.str("");
		ss << ts->tm_mday;
		replaceString(str, "|DAY|", ss.str());

		ss.str("");
		ss << (ts->tm_mon + 1);
		replaceString(str, "|MONTH|", ss.str());

		ss.str("");
		ss << (ts->tm_year + 1900);
		replaceString(str, "|YEAR|", ss.str());

		ss.str("");
		ss << ts->tm_wday;
		replaceString(str, "|WEEKDAY|", ss.str());

		ss.str("");
		ss << ts->tm_yday;
		replaceString(str, "|YEARDAY|", ss.str());

		ss.str("");
		ss << ts->tm_hour << ":" << ts->tm_min << ":" << ts->tm_sec;
		replaceString(str, "|TIME|", ss.str());

		ss.str("");
		replaceString(str, "|DATE|", formatDateShort(now, true));
	}

	s << std::endl << str;
	return s.str();
}

std::string Item::getNameDescription(const ItemType& it, const Item* item/* = NULL*/, int32_t subType/* = -1*/, bool addArticle/* = true*/)
{
	if(item)
		subType = item->getSubType();

	std::stringstream s;
	if(it.name.length() || (item && item->getName().length()))
	{
		if(subType > 1 && it.stackable && it.showCount)
			s << subType << " " << (item ? item->getPluralName() : it.pluralName);
		else
		{
			if(addArticle)
			{
				if(item && !item->getArticle().empty())
					s << item->getArticle() << " ";
				else if(!it.article.empty())
					s << it.article << " ";
			}

			s << (item ? item->getName() : it.name);
		}
	}
	else
		s << "an item of type " << it.id << ", please report it to gamemaster";

	return s.str();
}

std::string Item::getWeightDescription(double weight, bool stackable, uint32_t count/* = 1*/)
{
	if(weight > 0)
		return "";

	std::stringstream s;
	if(stackable && count > 1)
		s << "They weigh " << std::fixed << std::setprecision(2) << weight << " oz.";
	else
		s << "It weighs " << std::fixed << std::setprecision(2) << weight << " oz.";

	return s.str();
}

void Item::setUniqueId(uint16_t n)
{
	if(getUniqueId() && getActionId() != 2000)
		return;

	ItemAttributes::setUniqueId(n);
	ScriptEnviroment::addUniqueThing(this);
}

bool Item::canDecay()
{
	if(isRemoved())
		return false;

	if(isLoadedFromMap() && (getUniqueId() || (getActionId() && getContainer())))
		return false;

	const ItemType& it = Item::items[id];
	if(it.decayTo == -1 || it.decayTime == 0)
		return false;

	return true;
}

void Item::getLight(LightInfo& lightInfo)
{
	const ItemType& it = items[id];
	lightInfo.color = it.lightColor;
	lightInfo.level = it.lightLevel;
}

std::string ItemAttributes::emptyString("");

const std::string& ItemAttributes::getStrAttr(itemAttrTypes type) const
{
	if(!validateStrAttrType(type))
		return emptyString;

	if(Attribute* attr = getAttrConst(type))
		return *(std::string*)attr->value;

	return emptyString;
}

void ItemAttributes::setStrAttr(itemAttrTypes type, const std::string& value)
{
	if(!validateStrAttrType(type) || !value.length())
		return;

	Attribute* attr = getAttr(type);
	if(!attr)
		return;

	if(attr->value)
		delete (std::string*)attr->value;

	attr->value = (void*)new std::string(value);
}

bool ItemAttributes::hasAttribute(itemAttrTypes type) const
{
	if(!validateIntAttrType(type))
		return false;

	Attribute* attr = getAttrConst(type);
	return attr != NULL;
}

void ItemAttributes::removeAttribute(itemAttrTypes type)
{
	//check if we have it
	if((type & m_attributes))
	{
		//go trough the linked list until find it
		Attribute* prevAttr = NULL;
		Attribute* curAttr = m_firstAttr;
		while(curAttr != NULL)
		{
			if(curAttr->type == type)
			{
				//found so remove it from the linked list
				if(prevAttr)
					prevAttr->next = curAttr->next;
				else
					m_firstAttr = curAttr->next;

				//remove it from flags
				m_attributes = m_attributes & ~type;
				//delete string if it is string type
				if(validateStrAttrType(type))
					delete (std::string*)curAttr->value;

				//finally delete the attribute and return
				delete curAttr;
				return;
			}

			//advance in the linked list
			prevAttr = curAttr;
			curAttr = curAttr->next;
		}
	}
}

uint32_t ItemAttributes::getIntAttr(itemAttrTypes type) const
{
	if(!validateIntAttrType(type))
		return 0;

	if(Attribute* attr = getAttrConst(type))
		return static_cast<uint32_t>(0xFFFFFFFF & reinterpret_cast<ptrdiff_t>(attr->value));

	return 0;
}

void ItemAttributes::setIntAttr(itemAttrTypes type, int32_t value)
{
	if(!validateIntAttrType(type))
		return;

	if(Attribute* attr = getAttr(type))
		attr->value = reinterpret_cast<void*>(static_cast<ptrdiff_t>(value));
}

void ItemAttributes::increaseIntAttr(itemAttrTypes type, int32_t value)
{
	if(!validateIntAttrType(type))
		return;

	if(Attribute* attr = getAttr(type))
		attr->value = reinterpret_cast<void*>(static_cast<ptrdiff_t>(static_cast<uint32_t>(0xFFFFFFFF & reinterpret_cast<ptrdiff_t>(attr->value)) + value));
}

bool ItemAttributes::validateIntAttrType(itemAttrTypes type)
{
	switch(type)
	{
		case ATTR_ITEM_ACTIONID:
		case ATTR_ITEM_UNIQUEID:
		case ATTR_ITEM_OWNER:
		case ATTR_ITEM_DURATION:
		case ATTR_ITEM_DECAYING:
		case ATTR_ITEM_WRITTENDATE:
		case ATTR_ITEM_CORPSEOWNER:
		case ATTR_ITEM_CHARGES:
		case ATTR_ITEM_FLUIDTYPE:
		case ATTR_ITEM_DOORID:
		case ATTR_ITEM_ATTACK:
		case ATTR_ITEM_EXTRAATTACK:
		case ATTR_ITEM_DEFENSE:
		case ATTR_ITEM_EXTRADEFENSE:
		case ATTR_ITEM_ARMOR:
		case ATTR_ITEM_SCRIPTPROTECTED:
		case ATTR_ITEM_HITCHANCE:
		case ATTR_ITEM_SHOOTRANGE:
		case ATTR_ITEM_ATTACKSPEED:
			return true;

		default:
			break;
	}

	return false;
}

bool ItemAttributes::validateStrAttrType(itemAttrTypes type)
{
	switch(type)
	{
		case ATTR_ITEM_DESC:
		case ATTR_ITEM_TEXT:
		case ATTR_ITEM_WRITTENBY:
		case ATTR_ITEM_NAME:
		case ATTR_ITEM_PLURALNAME:
		case ATTR_ITEM_ARTICLE:
			return true;

		default:
			break;
	}

	return false;
}

void ItemAttributes::addAttr(Attribute* attr)
{
	if(m_firstAttr)
	{
		Attribute* curAttr = m_firstAttr;
		while(curAttr->next)
			curAttr = curAttr->next;

		curAttr->next = attr;
	}
	else
		m_firstAttr = attr;

	m_attributes = m_attributes | attr->type;
}

ItemAttributes::Attribute* ItemAttributes::getAttrConst(itemAttrTypes type) const
{
	if(!(type & m_attributes))
		return NULL;

	Attribute* curAttr = m_firstAttr;
	while(curAttr)
	{
		if(curAttr->type == type)
			return curAttr;

		curAttr = curAttr->next;
	}

	std::cout << "[Warning - ItemAttributes::getAttrConst] (type & m_attributes) but attribute not found" << std::endl;
	return NULL;
}

ItemAttributes::Attribute* ItemAttributes::getAttr(itemAttrTypes type)
{
	Attribute* curAttr;
	if(!(type & m_attributes))
	{
		curAttr = new Attribute(type);
		addAttr(curAttr);
		return curAttr;
	}

	curAttr = m_firstAttr;
	while(curAttr)
	{
		if(curAttr->type == type)
			return curAttr;

		curAttr = curAttr->next;
	}

	std::cout << "[Warning - ItemAttributes::getAttr] (type & m_attributes) but attribute not found" << std::endl;
	curAttr = new Attribute(type);

	addAttr(curAttr);
	return curAttr;
}

void ItemAttributes::deleteAttrs(Attribute* attr)
{
	if(!attr)
		return;

	if(validateStrAttrType(attr->type))
		delete (std::string*)attr->value;

	Attribute* nextAttr = attr->next;
	attr->next = NULL;
	if(nextAttr)
		deleteAttrs(nextAttr);

	delete attr;
}

void Item::__startDecaying()
{
	g_game.startDecay(this);
}
