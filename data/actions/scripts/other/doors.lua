local function doorEnter(cid, uid, id, position)
	doTransformItem(uid, id)
	doTeleportThing(cid, position)
	return true
end

function onUse(cid, item, fromPosition, itemEx, toPosition)
	if(fromPosition.x ~= CONTAINER_POSITION and isPlayerPzLocked(cid) and getTileInfo(fromPosition).protection) then
		doPlayerSendDefaultCancel(cid, RETURNVALUE_NOTPOSSIBLE)
		return true
	end

	local locked = DOORS[item.itemid]
	if(locked) then
		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is locked.")
		return true
	end

	local door = getItemInfo(item.itemid)
	if(door.levelDoor > 0) then
		if(item.actionid == 189) then
			if(not isPremium(cid)) then
				doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "Only the worthy may pass.")
				return true
			end

			return doorEnter(cid, item.uid, door.transformUseTo, toPosition)
		end

		local gender = item.actionid - 186
		if(isInArray({PLAYERSEX_FEMALE,  PLAYERSEX_MALE}, gender)) then
			if(gender ~= getPlayerSex(cid)) then
				doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "Only the worthy may pass.")
				return true
			end

			return doorEnter(cid, item.uid, door.transformUseTo, toPosition)
		end

		local skull = item.actionid - 180
		if(skull >= SKULL_NONE and skull <= SKULL_BLACK) then
			if(skull ~= getCreatureSkullType(cid)) then
				doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "Only the worthy may pass.")
				return true
			end

			return doorEnter(cid, item.uid, door.transformUseTo, toPosition)
		end

		local group = item.actionid - 150
		if(group >= 0 and group < 30) then
			if(group > getPlayerGroupId(cid)) then
				doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "Only the worthy may pass.")
				return true
			end

			return doorEnter(cid, item.uid, door.transformUseTo, toPosition)
		end

		local vocation = item.actionid - 100
		if(vocation >= 0 and vocation < 50) then
			local vocationEx = getVocationInfo(getPlayerVocation(cid))
			if(vocationEx.id ~= vocation and vocationEx.fromVocation ~= vocation) then
				doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "Only the worthy may pass.")
				return true
			end

			return doorEnter(cid, item.uid, door.transformUseTo, toPosition)
		end

		if(item.actionid == 190 or (item.actionid ~= 0 and getPlayerLevel(cid) >= (item.actionid - doors.levelDoor))) then
			return doorEnter(cid, item.uid, door.transformUseTo, toPosition)
		end

		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "Only the worthy may pass.")
		return true
	end

	if(door.specialDoor) then
		if(item.actionid == 100 or (item.actionid ~= 0 and getCreatureStorage(cid, item.actionid) > 0)) then
			return doorEnter(cid, item.uid, door.transformUseTo, toPosition)
		end

		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "The door seems to be sealed against unwanted intruders.")
		return true
	end

	toPosition.stackpos = STACKPOS_TOP_MOVEABLE_ITEM_OR_CREATURE
	local fields, thing = getTileItemsByType(fromPosition, ITEM_TYPE_MAGICFIELD), getThingFromPosition(toPosition)
	if(item.uid == thing.uid or thing.itemid < 100 or table.maxn(fields) ~= 0) then
		return true
	end

	local doorCreature = getThingFromPosition(toPosition)
	if(doorCreature.itemid ~= 0) then
		toPosition.x = toPosition.x - 1
		local query = doTileQueryAdd(doorCreature, toPosition, 20) -- allow to stack outside doors, but not on teleports or floor changing tiles
		if(query == RETURNVALUE_NOTPOSSIBLE) then
			toPosition.x = toPosition.x + 1
			toPosition.y = toPosition.y - 1
			query = doTileQueryAdd(doorCreature, toPosition, 20) -- repeat until found
		end

		if(query ~= RETURNVALUE_NOERROR) then
			doPlayerSendDefaultCancel(cid, query)
			return true
		end

		doTeleportThing(doorCreature.uid, toPosition)
		if(door.closingDoor) then
			doTransformItem(item.uid, door.transformUseTo)
		end

		return true
	end

	return false
end