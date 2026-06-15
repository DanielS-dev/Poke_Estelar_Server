local prizes = {
	[62001] = {egg = "Mew", outfit = 39229, multiplier = 1},
	[62002] = {egg = "Celebi", multiplier = 1},
	[62003] = {egg = "Jirachi", multiplier = 1},
	[62004] = {egg = "Deoxys", multiplier = 2},
	[62005] = {egg = "Darkrai", multiplier = 3},
	[62006] = {egg = "Shaymin", drop = {39149}, chance = 5, multiplier = 1},
	[62007] = {egg = "Arceus", drop = {39266, 39267, 39268, 39269, 39270, 39271, 39272, 39273, 39274, 39275, 39276, 39277, 39278, 39279, 39280, 39281, 39282}, chance = 5, multiplier = 3},
	[62008] = {egg = "Victini", multiplier = 1},
	[62009] = {egg = "Keldeo", multiplier = 1},
	[62010] = {egg = "Meloetta", multiplier = 1},
	[62011] = {egg = "Genesect", multiplier = 2},
	[62012] = {egg = "Diancie", multiplier = 3},
	[62013] = {egg = "Hoopa", drop = {39150}, chance = 5, multiplier = 3},
	[62014] = {egg = "Volcanion", multiplier = 3},
	[62015] = {egg = "Magearna", multiplier = 3},
	[62016] = {egg = "Marshadow", multiplier = 1},
	[62017] = {egg = "Zeraora", multiplier = 1},
	[62018] = {egg = "Melmetal", multiplier = 1},
	[62019] = {egg = "Zarude", multiplier = 3},
	
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if not player:hasKilledLegendaryPokemon() then
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao contribuiu para o abate do boss.")
		return true
	end
	if prizes[item.actionid] then
		local tokens = math.random(1, 3) * prizes[item.actionid].multiplier
		player:getInbox():addItem(2160, tokens, INDEX_WHEREEVER, FLAG_NOLIMIT)
		local str = "Voce recebeu: "..tokens.." crystal coins"
		player:teleportTo(Position({x=719,y=785,z=5}))
		if math.random(1, 10) <= 1 and prizes[item.actionid].outfit then
			player:getInbox():addItem(prizes[item.actionid].outfit, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
			str = str .. "rare outfit"
		end
		if math.random(1, 10) <= 1 then
			player:getInbox():addItem('pokepark ticket', 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
			str = str .. ", pokepark ticket"
		end
		-- if math.random(1, 1000) <= 3 then
			-- player:getInbox():addItem('100% loot charm', 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
			-- str = str .. ", 100% loot charm"
		-- end
		if prizes[item.actionid].drop then
			if math.random(1, 100) <= prizes[item.actionid].chance then
				local item = prizes[item.actionid].drop[math.random(1, #prizes[item.actionid].drop)]
				player:getInbox():addItem(item, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
				str = str .. ", "..getItemName(item)
			end
		end
		if math.random(1, 1000) <= 5 then
			local egg = player:getInbox():addItem(36570, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
			egg:setSpecialAttribute("eggname", prizes[item.actionid].egg)
			egg:setSpecialAttribute("steps", 0)
			str = str .. " e um ovo."
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, str .. " Os itens foram enviados para o depot.")
		player:save()
	end
	return true
end
