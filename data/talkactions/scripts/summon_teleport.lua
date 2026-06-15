local delay = 0
local availableCities = 3

function onSay(player, words, param)
	if param == "" then
		local msg = "Available cities: \n\n"
		for i = 1, availableCities do
			local town = Town(i)
			if town then
				msg = msg .. town:getName() .. "\n"
			end
		end
		player:showTextDialog(2263, msg)
		return false
	end

	if player:isPzLocked() then
		player:sendCancelMessage("Sorry, not possible while PZ locked.")
		return false		
	end

	local timeSinceLast = os.time() - player:getStorageValue(storageDelayTeleport)
	if timeSinceLast < delay then
		player:sendCancelMessage("Sorry, not possible. You need to wait " .. delay - timeSinceLast .. " seconds to teleport again.")
		return false		
	end

	if not hasSummons(player) then
		player:sendCancelMessage("Sorry, not possible. You need a pokemon to use teleport.")
		return false
	end

	local summon = player:getSummon()
	local summonName = summon:getName()
	local monsterType = MonsterType(summonName)
	local cantp = 0
	if monsterType:getRaceName() == "psychic" or monsterType:getRace2Name() == "psychic" then cantp = 1 end
	if monsterType:canTeleport() == 1 then cantp = 1 end
	if cantp == 0 then
		player:sendCancelMessage("Sorry, not possible. Your pokemon can not teleport.")
		return false		
	end

	local town = Town(param)
	if town == nil then
		town = Town(tonumber(param))
	end

	if town == nil then
		player:sendCancelMessage("Town not found.")
		return false
	end

	if town:getId() > availableCities then
		player:sendCancelMessage("Sorry, town not available.")
		return false
	end

	if town:getId() == 4 and player:getLevel() < 100 then
		player:sendCancelMessage("Voce precisa ser level 100 ou maior para acessar as Farlands.")
		return false
	end

	if player:isOnDive() then
		player:setStorageValue(storageDive, -1)
		player:removeCondition(CONDITION_OUTFIT)
	end

	if player:isDuelingWithNpc() then
		player:unsetDuelWithNpc()
	end
	
	if player:getCondition(CONDITION_SAFFARI) ~= nil then
		player:removeCondition(CONDITION_SAFFARI)
		if player:getItemCount(26685) >= 1 then
			player:removeItem(26685, player:getItemCount(26685))
		end
	end
	if player:getCondition(CONDITION_PARK) ~= nil then
		player:removeCondition(CONDITION_PARK)
		if player:getItemCount(39132) >= 1 then
			player:removeItem(39132, player:getItemCount(39132))
		end
	end

	player:say(summonName .. ", teleport me to " .. town:getName() .. "!", TALKTYPE_SAY)
	player:teleportTo(town:getTemplePosition())
	player:setStorageValue(storageDelayTeleport, os.time())
	return false
end
