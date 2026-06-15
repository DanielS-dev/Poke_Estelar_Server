local leverpos = {
	[64001] = Position(915, 748, 15),
}

local function removeItem()
	local tp = Tile(Position(915, 684, 15)):getItemById(1387) or 0
	if tp ~= 0 then tp:remove() end
end

local function doWalk(cid, direction, times)
	cid = Creature(cid)
	cid:move(direction)
	if times == 59 then
		 local portal = Game.createItem(1387, 1, Position(915, 684, 15))
		 if not portal:isTeleport() then
			portal:remove()
			return false
		 end
		 portal:setDestination(Position(908, 768, 15))
		 addEvent(removeItem, 5000)
	end
end

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if areaHasPlayer(Position(915, 716, 15), 3, 33) then return false end
	cleanArea(Position(915, 716, 15), 33, 33)
	local npc = Game.createNpc("Minecart", Position(915, 746, 15))
	for i = 1, 59 do
		addEvent(doWalk, i * 2000, npc.uid, 0, i)
	end
	player:teleportTo(leverpos[item.uid])
	return true
end


		
	