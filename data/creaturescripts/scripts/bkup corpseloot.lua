local stones = {"leaf stone", "boost stone", "water stone", "venom stone", "thunder stone", "rock stone", "punch stone", "fire stone", "ice stone", "cocoon stone", "crystal stone", "darkness stone", "earth stone", "enigma stone", "heart stone", "metal coat", "sun stone", "feather stone", "king's rock stone", "dragon stone"}

local function doSendMultipleEffects(pos, effect, times, interval)
	for i = 1, times do
		addEvent(doSendMagicEffect, i * interval, pos, effect)
	end
	return
end

local function spawnPoke(name, pos)
	Game.createMonster(name, pos)
end

function onPostDeath(creature, corpse, killer, mostDamage, unjustified, mostDamage_unjustified)
	if not corpse or not creature then
		return true
	end
	
	if type(corpse) ~= "userdata" then
		return true
	end
	
	local monsterType = MonsterType(creature:getName())
	if not monsterType or monsterType:getCorpseId() == 0 then
		return true
	end
	
	if not corpse:isContainer() then
		print("WARNING! Corpse not container, creature " .. pokename .. ".")
		return true
	end
	if not corpse:hasAttribute(ITEM_ATTRIBUTE_CORPSEOWNER) then
		print('no owner Killer: '..killer:getName()..'')
		return true
	end
	
	if not Player(killer) then
		print('No killer.')
		return true
	end
	
	local corpos = creature:getPosition()
	local player = Player(killer)
	local pokename = creature:getName()
	local pokelevel = creature:getLevel()
	
	local worldboss = {"Manaphy", "Giratina"}
	if isInArray(worldboss, pokename) then
		addEvent(spawnPoke, 60*60*1000, pokename, corpos)
		broadcastMessage("O World Boss ["..pokename.."] foi derrotado. Ele respawnara em 1 hora.", MESSAGE_STATUS_WARNING)
	elseif math.random(1, 100) <= 15 and pokename == "Ninjask" then
		Game.createMonster("Shedinja", corpos)
		corpos:sendMagicEffect(331)
	elseif math.random(1, 100) <= 1 and isInArray({"Bulbasaur", "Charmander", "Caterpie", "Weedle", "Pidgey", "Rattata", "Spearow", "Pikachu", "Clefairy", "Vulpix", "Jigglypuff", "Zubat", "Oddish", "Paras", "Diglett", "Mankey", "Abra", "Machop", "Bellsprout", "Magnemite", "Grimer", "Gastly", "Voltorb", "Koffing", "Tangela", "Eevee"}, pokename) then
		Game.createMonster("Ditto", corpos)
		corpos:sendMagicEffect(304)
	end
	
	if talismanTable[pokename:lower()] and math.random(1, 100000) <= 1 * talismanVar then
		local item = corpse:addItem(39319, 1)
		item:setSpecialAttribute("talisman", pokename:lower())
		doSendMultipleEffects(corpos, 56, 10, 600)
	end
	
	if player:getItemCount(39265) >= 1 then
		if monsterType:hasMega() > 0 then
			local chance = 1 * megaVar
			if isInRange(corpos, Position(1105, 1607, 15), Position(1313, 1720, 15)) then
				chance = 4 * megaVar
			end		
			if math.random(1, 100) <= chance then
				local megaName = "Mega " .. pokename
				if megaName == "Mega Charizard" then if math.random(1, 2) == 1 then megaName = megaName.." X" else megaName = megaName.." Y" end end
				local megaMonsterType = MonsterType(megaName)
				if not megaMonsterType then
					print("WARNING! " .. megaName .. " not found for respawn.")
				else
					Game.createMonster(megaName, corpos, false, true, 0, 0)
					player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Um mega spawnou pelo Rarity Charm")
					local pos = corpos
					pos:getNextPosition(1)
					pos:getNextPosition(2)
					pos:sendMagicEffect(1040)
				end
			end
		elseif not isInArray({"arceus", "kecleon"}, pokename:lower()) then
			local chance = 3 * teraVar
			if isInRange(corpos, Position(1105, 1607, 15), Position(1313, 1720, 15)) then
				chance = 12 * teraVar
			end
			if math.random(1, 1000) <= chance then
				local monstro = Game.createMonster(pokename, corpos, false, true, 0, 0)
				monstro:setSkull(math.random(11, 28))
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Um tera spawnou pelo Rarity Charm")
			end
		end
	end
	for i = corpse:getSize() - 1, 0, -1 do
		local item = corpse:getItem(i)
		if isInArray({39171, 39173, 39172, 39171, 39170, 39169, 39168, 39167, 39166, 39165, 39164, 39163, 39162, 39161, 39160, 39159, 39158, 39157, 39156, 39155, 39154, 39153, 39152, 39151, 39174, 39196, 39195, 39194, 39193, 39192, 39191, 39190, 39189, 39188, 39187, 39186, 39185, 39184, 39183, 39182, 39181, 39180, 39179, 39178, 39177, 39176, 39175}, item:getId()) then
			doSendMultipleEffects(corpos, 56, 10, 600)
		end
		if item:getId() == 36318 and tokenVar > 1 then
			corpse:addItem(36318, item:getCount() * (tokenVar - 1))
		end
	end
	if player and player:isPlayer() and player:isAutoLooting() then
		local msg = "[AUTOLOOT] "
		local nItems = 0
		for i = corpse:getSize() - 1, 0, -1 do
			local item = corpse:getItem(i)				
			if item then
				if hasEmptySpace(player:getSlotItem(CONST_SLOT_BACKPACK)) or player:getItemCount(item:getId()) >= 1 then
					local itemId = item:getId()
					local itemName = item:getName()
					local itemCount = item:getCount()
					msg = msg .. itemCount .. " " .. itemName .. ", "
					if itemId == 39319 then
						local toadd = player:addItem(itemId, itemCount)
						toadd:setSpecialAttribute("talisman", pokename:lower())
					else
						player:addItem(itemId, itemCount)
					end
					local itemstack = {2148, 2152, 27671, 27669, 38958, 38965, 38959, 38962, 27719, 38957, 38964, 38963, 27672, 27670, 27784, 1294, 27668, 38960, 38961, 7762}
					local toitem = {2152, 2160, 39241, 39242, 39243, 39244, 39245, 39246, 39247, 39248, 39249, 39250, 39251, 39252, 39253, 39254, 39255, 39256, 39257, 39258}
					for i = 1, #itemstack do
						if player:getItemCount(itemstack[i]) >= 100 then
							player:removeItem(itemstack[i], 100)
							player:addItem(toitem[i], 1)
						end
					end
					item:remove()
					if isInArray({39171, 39173, 39172, 39171, 39170, 39169, 39168, 39167, 39166, 39165, 39164, 39163, 39162, 39161, 39160, 39159, 39158, 39157, 39156, 39155, 39154, 39153, 39152, 39151, 39174, 39196, 39195, 39194, 39193, 39192, 39191, 39190, 39189, 39188, 39187, 39186, 39185, 39184, 39183, 39182, 39181, 39180, 39179, 39178, 39177, 39176, 39175, 39319}, itemId) then player:save() end
					nItems = nItems + 1
				end
			end
		end
		if nItems >= 1 then
			player:sendTextMessage(MESSAGE_INFO_DESCR, msg:sub(1, -3) .. ".")
		end
	end
	return true
end
