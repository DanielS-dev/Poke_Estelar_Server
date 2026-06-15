function onSay(player, words, param)
	local item = param:split('|')
	if item[1] == "bagbox" then
		local box = {"aerodactyl bag", "charizard bag", "chikorita bag", "dragonite bag", "eevee bag", "espeon bag", "flareon bag", "golduck bag", "haunter bag", "jolteon bag", "jynx bag", "machamp bag", "marowak bag", "mr. mime bag", "pidgeot bag", "pikachu bag", "sandslash bag", "scyther bag", "scizor bag", "sneasel bag", "snorlax bag", "umbreon bag", "vaporeon bag", "victrebeel bag", "wartortle bag", "mewtwo bag", "mew bag"}
		for i = 1, item[2] do
			if player:removeTokens(25) then
				player:addItem(box[math.random(1, #box)], 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x bag.")
	elseif item[1] == "heldbox" then
		local held = {"held attack", "held defense", "held experience", "held burn", "held poison", "held wing"}
		for i = 1, item[2] do
			if player:removeTokens(100) then
				player:addItem(held[math.random(1, #held)], 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x held.")
		-- player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Helds indisponiveis no momento.")
	elseif item[1] == "expshare" then
		for i = 1, item[2] do
			if player:removeTokens(250) then
				player:addItem('exp share', 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x exp share.")
	elseif item[1] == "linkingcord" then
		for i = 1, item[2] do
			if player:removeTokens(10) then
				player:addItem('linking cord', 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x linking cord.")
	elseif item[1] == "celular" then
		for i = 1, item[2] do
			if player:removeTokens(500) then
				player:addItem('celular', 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x celular.")
	elseif item[1] == "heavyball" then
		for i = 1, item[2] do
			if player:removeTokens(5) then
				player:addItem('empty heavyball', 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x heavy ball.")
	elseif item[1] == "duskball" then
		for i = 1, item[2] do
			if player:removeTokens(5) then
				player:addItem('empty duskball', 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x dusk ball.")
	elseif item[1] == "loveball" then
		for i = 1, item[2] do
			if player:removeTokens(5) then
				player:addItem('empty loveball', 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x love ball.")
	elseif item[1] == "netball" then
		for i = 1, item[2] do
			if player:removeTokens(5) then
				player:addItem('empty netball', 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x net ball.")
	elseif item[1] == "premierball" then
		for i = 1, item[2] do
			if player:removeTokens(5) then
				player:addItem('empty premierball', 1)
			else
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tinha dinheiro para tudo, sua compra foi parcialmente finalizada.")
				return false
			end
		end
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce adquiriu "..item[2].."x premier ball.")
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Desculpe, nao vendo este item.")
		return false
	end
	return false
end
	