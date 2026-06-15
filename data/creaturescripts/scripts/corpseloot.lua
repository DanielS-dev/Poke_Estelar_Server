local stones = {"leaf stone", "boost stone", "water stone", "venom stone", "thunder stone", "rock stone", "punch stone", "fire stone", "ice stone", "cocoon stone", "crystal stone", "darkness stone", "earth stone", "enigma stone", "heart stone", "metal coat", "sun stone", "feather stone", "king's rock stone", "dragon stone"}
local loottable = {
	["water"] = {x1000 = {27668}, x100 = {27678, 27720, 27721}}, -- Water Gem, Water Pendant, Pot of Pure Water
	["normal"] = {x1000 = {38964}, x100 = {27681}}, -- Rubber Ball, Bitten Apple
	["fire"] = {x1000 = {27669}, x100 = {27656, 27745, 28571}}, -- Essence of Fire, Pot of Lava, Lava Pendant, Fire Orb
	["dark"] = {x1000 = {27784}, x100 = {39063}}, -- Dark Gem, Dark Orb
	["electric"] = {x1000 = {27671}, x100 = {28570}}, -- Screw, Thunder Orb
	["fairy"] = {x1000 = {7762}, x100 = {39064}}, -- Fairy Essence, Fairy Orb
	["ghost"] = {x1000 = {38963}, x100 = {27722, 27710}}, -- Essence of Darkness, Evil Pendant, Traces of Ghost
	["ground"] = {x1000 = {38965}, x100 = {27685}}, -- Earth Ball, Sandbag
	["psychic"] = {x1000 = {38959}, x100 = {27700}}, -- Enchanted Gem, Future Orb
	["steel"] = {x1000 = {38961}, x100 = {39065}}, -- Piece of Steel, Gold Ingot
	["bug"] = {x1000 = {38957}, x100 = {27658, 27679}}, -- Bug Gosme, Bag of Pollem, Pot of Moss Bug
	["dragon"] = {x1000 = {38962}, x100 = {18422}}, -- Dragon Essence, Dragon Orb
	["fighting"] = {x1000 = {38960}, x100 = {39066}}, -- Band-aid, Protein Bar
	["flying"] = {x1000 = {27719}, x100 = {27706}}, -- Straw, Feather
	["grass"] = {x1000 = {27670}, x100 = {27660, 27742}}, -- Seed, Leaves, Nature Pendant
	["ice"] = {x1000 = {38958}, x100 = {27707, 28569}}, -- Snow Ball, Ice Orb, Glacial Orb
	["poison"] = {x1000 = {27672}, x100 = {27759}}, -- Bottle of Poison, Bag of Poisonous Dust
	["rock"] = {x1000 = {1294}, x100 = {27702}}, -- Small Stone, Stone Orb
}

local function doSendMultipleEffects(pos, effect, times, interval)
	for i = 1, times do
		addEvent(doSendMagicEffect, i * interval, pos, effect)
	end
	return
end

local function doBody(owner, position)
	local corpse = Game.createItem(39260, 1, position)
	corpse:setAttribute(ITEM_ATTRIBUTE_CORPSEOWNER, owner)
	corpse:decay()
end

local function spawnPoke(name, pos)
	Game.createMonster(name, pos)
end

function onPostDeath(creature, corpse, killer, mostDamage, unjustified, mostDamage_unjustified)
	if isInRange(creature:getPosition(), Position(2411, 0, 0), Position(2733, 351, 7)) then
		local boss = {"Kleavor", "Wyrdeer", "Ursaluna", "Basculegion", "Sneasler", "Overqwil", "Toedscruel", "Wugtrio", "Annihilape", "Clodsire", "Farigiraf", "Dudunsparce", "Iron Bundle"}
		creature:getPosition():sendMagicEffect(1092)
		local loot = Game.createItem(39260, 1, creature:getPosition())
		local player = Player(killer)
		if player and player:isPlayer() and player:isAutoLooting() then
			loot = player
		else
			loot:setAttribute(ITEM_ATTRIBUTE_CORPSEOWNER, killer:getId())
			loot:decay()
		end
		if math.random(1, 1000) <= 5 and not isInArray(boss, creature:getName()) and not isInArray({"Mega Audino"}, creature:getName()) then
			local egg = player:getInbox():addItem(36570, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
			egg:setSpecialAttribute("eggname", creature:getName())
			egg:setSpecialAttribute("steps", 0)
		end
		if creature:getName() == "Mega Audino" and math.random(1, 10000) <= 10 then
			loot:addItem(39167, 1)
		end
		if isInArray(boss, creature:getName()) and math.random(1, 1000) <= 5 then
			loot:addItem(34765, 1)
		end
		if math.random(1, 100) <= 1 then
			if not isInArray(boss, creature:getName()) then
				local monstro = Game.createMonster(boss[math.random(1, #boss)], creature:getClosestFreePosition(creature:getPosition()))
				addEvent(doRemoveCreature, 5*60*1000, monstro.uid)
				monstro:setMaxHealth(monstro:getHealth() * 25)
				monstro:setHealth(monstro:getMaxHealth())
				local pos = monstro:getPosition()
				pos:getNextPosition(1)
				pos:getNextPosition(2)
				pos:sendMagicEffect(1047)
			end
		end
	end
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
	
	local worldboss = {"Manaphy", "Giratina"}
	if isInArray(worldboss, creature:getName()) then
		addEvent(spawnPoke, 60*60*1000, creature:getName(), creature:getPosition())
		broadcastMessage("O World Boss ["..creature:getName().."] foi derrotado. Ele respawnara em 1 hora.", MESSAGE_STATUS_WARNING)
	elseif math.random(1, 100) <= 15 and creature:getName() == "Ninjask" then
		Game.createMonster("Shedinja", creature:getPosition())
		creature:getPosition():sendMagicEffect(331)
	elseif math.random(1, 100) <= 1 and isInArray({"Bulbasaur", "Charmander", "Caterpie", "Weedle", "Pidgey", "Rattata", "Spearow", "Pikachu", "Clefairy", "Vulpix", "Jigglypuff", "Zubat", "Oddish", "Paras", "Diglett", "Mankey", "Abra", "Machop", "Bellsprout", "Magnemite", "Grimer", "Gastly", "Voltorb", "Koffing", "Tangela", "Eevee"}, creature:getName()) then
		Game.createMonster("Ditto", creature:getPosition())
		creature:getPosition():sendMagicEffect(304)
	end
	
	if not corpse:isContainer() then
		print("WARNING! Corpse not container, creature " .. creature:getName() .. ".")
		return true
	end
	if not corpse:hasAttribute(ITEM_ATTRIBUTE_CORPSEOWNER) then
		return true
	end
	local owner = corpse:getAttribute(ITEM_ATTRIBUTE_CORPSEOWNER)
	if not owner then
		return true
	end
	
	if talismanTable[creature:getName():lower()] and math.random(1, 100000) <= 1 * talismanVar then
		local item = corpse:addItem(39319, 1)
		item:setSpecialAttribute("talisman", creature:getName():lower())
		doSendMultipleEffects(creature:getPosition(), 56, 10, 600)
	end
	
	local player = Player(killer)
	
	if player:getItemCount(39265) >= 1 then
		if monsterType:hasMega() > 0 then
			local chance = 1 * megaVar
			if isInRange(creature:getPosition(), Position(1105, 1607, 15), Position(1313, 1720, 15)) then
				chance = 4 * megaVar
			end		
			if math.random(1, 100) <= chance then
				local megaName = "Mega " .. creature:getName()
				if megaName == "Mega Charizard" then if math.random(1, 2) == 1 then megaName = megaName.." X" else megaName = megaName.." Y" end end
				local megaMonsterType = MonsterType(megaName)
				if not megaMonsterType then
					print("WARNING! " .. megaName .. " not found for respawn.")
				else
					Game.createMonster(megaName, creature:getPosition(), false, true, 0, 0)
					player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Um mega spawnou pelo Rarity Charm")
					local pos = creature:getPosition()
					pos:getNextPosition(1)
					pos:getNextPosition(2)
					pos:sendMagicEffect(1040)
				end
			end
		elseif not isInArray({"arceus", "kecleon"}, creature:getName():lower()) then
			local chance = 3 * teraVar
			if isInRange(creature:getPosition(), Position(1105, 1607, 15), Position(1313, 1720, 15)) then
				chance = 12 * teraVar
			end
			if math.random(1, 1000) <= chance then
				local monstro = Game.createMonster(creature:getName(), creature:getPosition(), false, true, 0, 0)
				monstro:setSkull(math.random(11, 28))
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Um tera spawnou pelo Rarity Charm")
			end
		end
	end
	
	for i = corpse:getSize() - 1, 0, -1 do
		local item = corpse:getItem(i)
		if isInArray({39171, 39173, 39172, 39171, 39170, 39169, 39168, 39167, 39166, 39165, 39164, 39163, 39162, 39161, 39160, 39159, 39158, 39157, 39156, 39155, 39154, 39153, 39152, 39151, 39174, 39196, 39195, 39194, 39193, 39192, 39191, 39190, 39189, 39188, 39187, 39186, 39185, 39184, 39183, 39182, 39181, 39180, 39179, 39178, 39177, 39176, 39175}, item:getId()) then
			doSendMultipleEffects(creature:getPosition(), 56, 10, 600)
		end
		if item:getId() == 36318 and tokenVar > 1 then
			corpse:addItem(36318, item:getCount() * (tokenVar - 1))
		end
	end
	player = Player(owner)
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
						toadd:setSpecialAttribute("talisman", creature:getName():lower())
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
