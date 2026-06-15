local playerPosition = {
	{x = 635, y = 993, z = 8},
	{x = 636, y = 994, z = 8},
	{x = 637, y = 993, z = 8}
	
}
local newPosition = {
	{x = 510, y = 480, z = 15},
	{x = 513, y = 485, z = 15},
	{x = 517, y = 480, z = 15}
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local players = {}
	for _, position in ipairs(playerPosition) do
		local topPlayer = Tile(position):getTopCreature()
		if topPlayer == nil or not topPlayer:isPlayer() then
			player:sendTextMessage(MESSAGE_STATUS_SMALL, Game.getReturnMessage(RETURNVALUE_NOTPOSSIBLE))
			return false
		end
		players[#players + 1] = Player(topPlayer):getId()
	end
	if not isInArray(players, player:getId()) then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voces nao esta na area.")
		return false
	end
	if areaHasPlayer(Position(514, 473, 15), 12, 12) then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Alguem esta na Raid agora, aguarde um instante.")
		return false
	end
	cleanArea(Position(514, 480, 15), 12, 12)
	for i = 1, #players do
		Player(players[i]):teleportTo(newPosition[i], false)
		Player(players[i]):getPosition():sendMagicEffect(CONST_ME_ENERGYAREA)
	end
	local monster = Game.createMonster("Lugia", Position(514, 480, 15))
	local condition = Condition(CONDITION_PARALYZE)
	condition:setParameter(CONDITION_PARAM_TICKS, -1)
	condition:setParameter(CONDITION_PARAM_SPEED, -1000)
	monster:addCondition(condition)
	return true
end
