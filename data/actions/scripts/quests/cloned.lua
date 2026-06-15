local playerPosition = {
	{x = 1132, y = 759, z = 11},
	{x = 1131, y = 759, z = 11},
	{x = 1130, y = 759, z = 11},
	{x = 1129, y = 759, z = 11}
}
local newPosition = {
	{x = 1149, y = 760, z = 11},
	{x = 1148, y = 760, z = 11},
	{x = 1147, y = 760, z = 11},
	{x = 1146, y = 760, z = 11}
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if item.itemid == 9826 then
		local players = {}
		for _, position in ipairs(playerPosition) do
			local topPlayer = Tile(position):getTopCreature()
			if topPlayer == nil or not topPlayer:isPlayer() or topPlayer:getLevel() < 1 then
				player:sendTextMessage(MESSAGE_STATUS_SMALL, Game.getReturnMessage(RETURNVALUE_NOTPOSSIBLE))
				return false
			end
			players[#players + 1] = topPlayer
		end

		for i, targetPlayer in ipairs(players) do
			Position(playerPosition[i]):sendMagicEffect(CONST_ME_POFF)
			targetPlayer:teleportTo(newPosition[i], false)
			targetPlayer:getPosition():sendMagicEffect(CONST_ME_ENERGYAREA)
		end
		item:transform(9825)
	elseif item.itemid == 9825 then
		item:transform(9826)
		player:sendTextMessage(MESSAGE_STATUS_SMALL, Game.getReturnMessage(RETURNVALUE_NOTPOSSIBLE))
	end
	return true
end
