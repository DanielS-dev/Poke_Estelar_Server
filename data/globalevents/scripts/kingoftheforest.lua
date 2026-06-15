local datas = {"Saturday", "Friday", "Thursday", "Tuesday"}

local function doBroad()
	broadcastMessage("O Evento Rei da Floresta vai acontecer, va ate o castelo ao norte de Saffron para participar.", MESSAGE_STATUS_WARNING)
end

local function doStart()
	local spectators = Game.getSpectators(Position(643, 412, 6), false, true, 0, 2, 0, 2)
	local players = {}
	for i = 1, #spectators do
		local spectator = spectators[i]
		if spectator:isPlayer() and not spectator:isNpc() then
			if spectator ~= creature then
				targets[#targets + 1] = spectator.uid
			end
		end
	end
	if #players < 5 then
		broadcastMessage("O Rei da Floresta nao inciou pois nao ha jogadores o suficiente.", MESSAGE_STATUS_WARNING)
		return true
	end
	for i = 1, #players do
		local jogador = Player(players[i])
		if jogador then
			local blockitem = {27645, 27642, 27643, 27641, 27647, 27646}
			for z = 1, #blockitem do
				if player:getItemCount(blockitem[z]) >= 1 then
					player:getInbox():addItem(blockitem[z], player:getItemCount(blockitem[z]), INDEX_WHEREEVER, FLAG_NOLIMIT)
					player:removeItem(blockitem[z], player:getItemCount(blockitem[z]))
				end
			end
			local positions = {Position(145, 47, 15), Position(145, 49, 15), Position(144, 48, 15), Position(146, 48, 15)}
			jogador:teleportTo(positions[math.random(1, #positions)])
		end
	end
	broadcastMessage("As inscricoes para o evento Rei da Floresta se encerraram. O evento comeca agora.", MESSAGE_STATUS_WARNING)
end

function onTime(interval) -- okay
	local dia = os.date("%A")
	if isInArray(datas, dia) then
		local npc = Game.createNpc("Tournment", Position(639, 412, 6))
		addEvent(doRemoveCreature, 15*60*1000, npc.uid)
		setGlobalStorageValue(3000, 'open') -- Status do evento
		broadcastMessage("O Evento Rei da Floresta vai acontecer, va ate o castelo ao norte de Saffron para participar.", MESSAGE_STATUS_WARNING)
		for i = 1, 4 do
			addEvent(doBroad, (i * 3)*60*1000)
		end
		addEvent(doStart, 15*60*1000)
	end
	return true
end