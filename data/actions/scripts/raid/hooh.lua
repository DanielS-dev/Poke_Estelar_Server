local playerPosition = {
	{x = 51, y = 445, z = 2},
	{x = 50, y = 446, z = 2},
	{x = 52, y = 446, z = 2},
	{x = 51, y = 447, z = 2}
	
}
local newPosition = {
	{x = 570, y = 480, z = 15},
	{x = 574, y = 480, z = 15},
	{x = 570, y = 484, z = 15},
	{x = 574, y = 484, z = 15}
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
	if areaHasPlayer(Position(572, 482, 15), 5, 5) then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Alguem esta na Raid agora, aguarde um instante.")
		return false
	end
	cleanArea(Position(572, 482, 15), 5, 5)
	for i = 1, #players do
		Player(players[i]):teleportTo(newPosition[i], false)
		Player(players[i]):getPosition():sendMagicEffect(CONST_ME_ENERGYAREA)
	end
	local monster = Game.createMonster("Ho-oh", Position(572, 482, 15))
	local condition = Condition(CONDITION_PARALYZE)
	condition:setParameter(CONDITION_PARAM_TICKS, -1)
	condition:setParameter(CONDITION_PARAM_SPEED, -1000)
	monster:addCondition(condition)
	return true
end
