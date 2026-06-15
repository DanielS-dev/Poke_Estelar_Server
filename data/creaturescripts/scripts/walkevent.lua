function doStepEggs(container, player)
	player = Player(player)
	local size = container:getSize()
	for i = size - 1, 0, -1 do
		local item = container:getItem(i)
		if item:getSpecialAttribute("steps") and item:getSpecialAttribute("steps") >= 0 then
			if player:getSummon() and isInArray(hiddenabilities.flamebody, player:getSummon():getName()) then
				item:setSpecialAttribute("steps", item:getSpecialAttribute("steps") + 2)
			else
				item:setSpecialAttribute("steps", item:getSpecialAttribute("steps") + 1)
			end
			if player:getSummon() then
				local talisman = player:getUsingBall():getSpecialAttribute('talisman') or 0
				if talismanTable[talisman] and talismanTable[talisman].buff == "egg" then
					item:setSpecialAttribute("steps", item:getSpecialAttribute("steps") + talismanTable[talisman].amount)
				end
			end
			
			if item:getSpecialAttribute("steps") >= 5000 then
				item:remove()
				local addPokeball = player:getInbox():addItem(26661, 1, INDEX_WHEREEVER, FLAG_NOLIMIT)
				addPokeball:setSpecialAttribute("pokeName", item:getSpecialAttribute("eggname"))
				addPokeball:setSpecialAttribute("pokeLevel", 1)
				addPokeball:setSpecialAttribute("pokeExperience", 0)
				addPokeball:setSpecialAttribute("pokeBoost", 0)
				addPokeball:setSpecialAttribute("pokeMaxHealth", MonsterType(item:getSpecialAttribute("eggname")):getMaxHealth())
				addPokeball:setSpecialAttribute("pokeHealth", MonsterType(item:getSpecialAttribute("eggname")):getMaxHealth())
				addPokeball:setSpecialAttribute("pokeLove", 50)
				addPokeball:setSpecialAttribute("evhp", 0)
				addPokeball:setSpecialAttribute("evatk", 0)
				addPokeball:setSpecialAttribute("evdef", 0)
				addPokeball:setSpecialAttribute("evpoints", 0)
				addPokeball:setSpecialAttribute("evkills", 0)
				if math.random(1, 1000) <= 50 * teraVar and item:getSpecialAttribute("eggname") ~= "Arceus" then
					addPokeball:setSpecialAttribute("teraType", math.random(11, 28))
				end
				local natures = {"Hardy", "Docile", "Bashful", "Quirky", "Serious", "Lonely", "Adamant", "Naughty", "Brave", "Bold", "Impish", "Lax", "Relaxed", "Modest", "Mild", "Rash", "Quiet", "Calm", "Gentle", "Careful", "Sassy", "Timid", "Hasty", "Jolly", "Naive"}
				if player:getSummon() and isInArray(hiddenabilities.synchronize, player:getSummon():getName()) and math.random(1, 100) <= 10 then
					if player:getUsingBall() and player:getUsingBall():getSpecialAttribute('nature') then
						addPokeball:setSpecialAttribute("nature", player:getUsingBall():getSpecialAttribute('nature'))
					else
						addPokeball:setSpecialAttribute("nature", natures[math.random(1, #natures)])
					end
				else
					addPokeball:setSpecialAttribute("nature", natures[math.random(1, #natures)])
				end
				-- local eggpoints = player:getStorageValue(6546516) or 0
				-- player:setStorageValue(6546516, eggpoints + 1)
				player:refreshPokemonBar({}, {})
				player:save()
			end
		elseif item:getSpecialAttribute("steps") and item:getSpecialAttribute("steps") < 0 then
			if player:getSummon() and isInArray(hiddenabilities.flamebody, player:getSummon():getName()) then
				item:setSpecialAttribute("steps", 2)
			else
				item:setSpecialAttribute("steps", 1)
			end
		elseif item:isContainer() then
			doStepEggs(item, player.uid)
		end
	end
end

function onMove(creature, toPosition, fromPosition)
	if not Player(creature:getId()) then return true end
	local player = Player(creature:getId())
	if player and player:isOnFly() then
		return true
	end
	
	-- Anti bag system
	
	if player:getBackpacks() > 10 then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce possui mais de 10 backpacks, deposite algumas no depot.")
		return false
	end
	
	-- Bike Effect System
	
	if player:getStorageValue(storageBike) == 1 and not isInArray({2801, 2795, 2800, 2793, 2798, 2792, 2799, 2791, 2790, 2789, 2802, 2794, 4057, 4056, 1315, 1316}, player:getOutfit().lookType) then
		if player:getItemCount(39318) >= 1 then
			fromPosition:sendMagicEffect(28)
		end
	end
	
	-- Egg System
	
	if player:getItemCount(36570) >= 1 and not Tile(toPosition):getHouse() then
		local backpack = player:getSlotItem(CONST_SLOT_BACKPACK)	
		doStepEggs(backpack, player.uid)
	end
	
	-- Pickup Ability
	
	if player:getSummon() and isInArray(hiddenabilities.pickup, player:getSummon():getName()) then
		if (player:getUsingBall():getSpecialAttribute('held') and player:getUsingBall():getSpecialAttribute('held') == 0) or not player:getUsingBall():getSpecialAttribute('held') then
			local common = {"gold coin", "empty pokeball", "small potion"}
			local uncommon = {"clean disk", "empty greatball", "great potion"}
			local rare = {"platinum coin", "water stone", "fire stone", "leaf stone", "thunder stone", "ice stone", "empty ultraball", "ultra potion", "revive"}
			local superrare = {"rare candy", "crystal coin", "king's rock", "moon stone", "upgrade", "dubious disk", "metal coat", "sun stone", "dragon scale", "protector", "magmarizer", "electirizer", "empty premierball", "hyper potion"}
			local chance = math.random(1, 100)
			if chance <= 1 then
				player:getUsingBall():setSpecialAttribute('held', superrare[math.random(1, #superrare)])
			elseif chance <= 4 then
				player:getUsingBall():setSpecialAttribute('held', rare[math.random(1, #rare)])
			elseif chance <= 10 then
				player:getUsingBall():setSpecialAttribute('held', uncommon[math.random(1, #uncommon)])
			elseif chance <= 30 then
				player:getUsingBall():setSpecialAttribute('held', common[math.random(1, #common)])
			end
		end
	end
	
	return true
end
