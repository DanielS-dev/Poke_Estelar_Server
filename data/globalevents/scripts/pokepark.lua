local datas = {"Thursday", "Tuesday", "Saturday", "Sunday"}

local function doBroad()
	broadcastMessage("As inscricoes para o PokePARK estao abertas. Va ate Port Harbor para se registrar.", MESSAGE_STATUS_WARNING)
end

local function doUpdate()
	local lista = getGlobalStorageValue(2004)
	local players = {}
	local ranking = {}
	for word in string.gmatch(lista, "%a+") do
		players[#players + 1] = word
	end
	for i = 1, #players do
		local jogador = Player(getPlayerByName(players[i]))
		if jogador then
			ranking[#ranking + 1] = {points = jogador:getStorageValue(1905001), name = players[i]}
		end
	end
	table.sort(ranking, function (k1, k2) return k1.points > k2.points end )
	for i = 1, 3 do
		local jogador = Player(getPlayerByName(ranking[i].name))
		setGlobalStorageValue(2000 + i, jogador)
	end
	broadcastMessage("PokePARK ranking: 1st "..getGlobalStorageValue(2001)..", 2nd "..getGlobalStorageValue(2002)..", 3rd "..getGlobalStorageValue(2003)..". Proxima atualizacao em 5 minutos.", MESSAGE_STATUS_WARNING)
end

local function doEnd()
	local lista = getGlobalStorageValue(2004)
	local players = {}
	for word in string.gmatch(lista, "%a+") do
		players[#players + 1] = word
	end
	for i = 1, #players do
		local player = Player(getPlayerByName(players[i]))
		if player then
			player:teleportTo(Position(1180, 1658, 7))
			player:removeCondition(CONDITION_PARK)
			if player:getItemCount(39132) >= 1 then
				player:removeItem(39132, player:getItemCount(39132))
			end
			local pontos = player:getStorageValue(1905002) or 0
			if pontos < 0 then pontos = 0 end
			if Player(getPlayerByName(getGlobalStorageValue(2001))) and getGlobalStorageValue(2001) == player:getName() then
				player:setStorageValue(1905002, pontos + 150)
				player:addItem(26683, 15)
			elseif Player(getPlayerByName(getGlobalStorageValue(2002))) and getGlobalStorageValue(2002) == player:getName() then
				player:setStorageValue(1905002, pontos + 75)
				player:addItem(26683, 10)
			elseif Player(getPlayerByName(getGlobalStorageValue(2003))) and getGlobalStorageValue(2003) == player:getName() then
				player:setStorageValue(1905002, pontos + 50)
				player:addItem(26683, 5)
			else
				player:setStorageValue(1905002, pontos + 25)
			end
			player:setStorageValue(1905001, 0)
		end
	end
	if Player(getPlayerByName(getGlobalStorageValue(2001))) and Player(getPlayerByName(getGlobalStorageValue(2002))) and Player(getPlayerByName(getGlobalStorageValue(2003))) then
		broadcastMessage("Parabens aos jogadores: "..getGlobalStorageValue(2001)..", "..getGlobalStorageValue(2002)..", "..getGlobalStorageValue(2003)..", por ficarem no podium do PokePARK.", MESSAGE_STATUS_WARNING)
	end
end

local function doStart()
	setGlobalStorageValue(2000, 'close')
	broadcastMessage("As inscricoes para o PokePARK se encerraram, o evento esta comecando.", MESSAGE_STATUS_WARNING)
	local lista = getGlobalStorageValue(2004)
	local players = {}
	for word in string.gmatch(lista, "%a+") do
		players[#players + 1] = word
	end
	if #players < 3 then
		broadcastMessage("O PokePARK nao inciou pois nao ha jogadores o suficiente.", MESSAGE_STATUS_WARNING)
		for i = 1, #players do
			local jogador = Player(getPlayerByName(players[i]))
			if jogador then
				jogador:addItem('pokepark ticket', 1)
			end
		end
		return true
	end
	for i = 1, #players do
		local jogador = Player(getPlayerByName(players[i]))
		if jogador then
			if jogador:getCondition(CONDITION_SAFFARI) ~= nil then
				player:removeCondition(CONDITION_SAFFARI)
				if player:getItemCount(26685) >= 1 then
					player:removeItem(26685, player:getItemCount(26685))
				end
			end
			local condition = Condition(CONDITION_PARK)
			condition:setTicks(-1)
			jogador:addCondition(condition)
			jogador:teleportTo(Position(942, 1725, 13))
			jogador:addItem(39132, 50)
		end
	end
	setGlobalStorageValue(2001, players[1]) -- Top 1
	setGlobalStorageValue(2002, players[1]) -- Top 2
	setGlobalStorageValue(2003, players[1]) -- Top 3
	addEvent(doEnd, 30*60*1000)
	for i = 1, 11 do
		addEvent(doUpdate, i*5*60*1000)
	end
end

function onTime(interval)
	local dia = os.date("%A")
	if isInArray(datas, dia) then
		setGlobalStorageValue(2000, 'open') -- Status do evento
		setGlobalStorageValue(2004, '') -- Lista de inscritos
		setGlobalStorageValue(2001, '') -- Top 1
		setGlobalStorageValue(2002, '') -- Top 2
		setGlobalStorageValue(2003, '') -- Top 3
		broadcastMessage("As inscricoes para o PokePARK estao abertas. Va ate Port Harbor para se registrar.", MESSAGE_STATUS_WARNING)
		for i = 1, 4 do
			addEvent(doBroad, (i * 3)*60*1000)
		end
		addEvent(doStart, 15*60*1000)
	end
	return true
end
