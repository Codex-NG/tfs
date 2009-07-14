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
#include "trashholder.h"

#include "spells.h"
#include "game.h"
extern Game g_game;

TrashHolder::TrashHolder(uint16_t _type, MagicEffectClasses _effect/* = NM_ME_NONE*/):
	Item(_type)
{
	effect = _effect;
}

void TrashHolder::__addThing(Creature* actor, int32_t index, Thing* thing)
{
	if(Item* item = thing->getItem())
	{
		if(item == this || !item->hasProperty(MOVEABLE))
			return;

		if(getTile()->isSwimmingPool())
		{
			if(item->getID() == ITEM_WATERBALL_SPLASH)
				return;

			if(item->getID() == ITEM_WATERBALL)
			{
				g_game.transformItem(item, ITEM_WATERBALL_SPLASH);
				return;
			}
		}

		g_game.internalRemoveItem(actor, item);
		if(effect != NM_ME_NONE)
			g_game.addMagicEffect(getPosition(), effect);
	}
	else if(getTile()->isSwimmingPool(false))
	{
		if(Creature* creature = thing->getCreature())
		{
			if(Player* player = creature->getPlayer())
			{
				if(player->getPosition() == player->getLastPosition()) //player just logged in swimming pool
				{
					Outfit_t outfit;
					outfit.lookType = 267;
					Spell::CreateIllusion(player, outfit, -1);
				}
			}
		}
	}
}

void TrashHolder::postAddNotification(Creature* actor, Thing* thing, const Cylinder* oldParent,
	int32_t index, cylinderlink_t link /*= LINK_OWNER*/)
{
	getParent()->postAddNotification(actor, thing, oldParent, index, LINK_PARENT);
}

void TrashHolder::postRemoveNotification(Creature* actor, Thing* thing, const Cylinder* newParent,
	int32_t index, bool isCompleteRemoval, cylinderlink_t link /*= LINK_OWNER*/)
{
	getParent()->postRemoveNotification(actor, thing, newParent,
		index, isCompleteRemoval, LINK_PARENT);
}
