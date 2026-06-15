local playerPosition = {
	{x = 803, y = 842, z = 7},
	{x = 805, y = 842, z = 7},
	{x = 803, y = 843, z = 7},
	{x = 804, y = 843, z = 7},
	{x = 805, y = 843, z = 7}
	
}
local newPosition = {
	{x = 617, y = 515, z = 15},
	{x = 618, y = 515, z = 15},
	{x = 619, y = 515, z = 15},
	{x = 620, y = 515, z = 15},
	{x = 621, y = 515, z = 15}
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
	player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, tostring(getPartyMembers(player)[2]))
	if not isInArray(players, player:getId()) then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voces nao esta na area.")
		return false
	end
	if areaHasPlayer(Position(620, 502, 15), 13, 13) or areaHasPlayer(Position(620, 470, 15), 13, 13) then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Alguem esta na Raid agora, aguarde um instante.")
		return false
	end
	cleanArea(Position(620, 502, 15), 13, 13)
	cleanArea(Position(620, 470, 15), 13, 13)
	for i = 1, #players do
		Player(players[i]):teleportTo(newPosition[i], false)
		Player(players[i]):getPosition():sendMagicEffect(CONST_ME_ENERGYAREA)
	end
	local monster = Game.createMonster("Darkrai", Position(620, 470, 15))
	local condition = Condition(CONDITION_PARALYZE)
	condition:setParameter(CONDITION_PARAM_TICKS, -1)
	condition:setParameter(CONDITION_PARAM_SPEED, -1000)
	monster:addCondition(condition)
	return true
end
