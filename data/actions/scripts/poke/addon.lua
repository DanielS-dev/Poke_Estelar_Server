function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if item:getSpecialAttribute("addon") == nil then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Este magical cloth nao esta com nenhum addon registrado nele.")
		return false
	end
	
	if not hasSummons(player) then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu pokemon precisa estar para fora para evoluir.")
		return false
	end
	
	if not isSummon(target) then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce so pode usar isso em um pokemon seu.")
		return false
	end
	
	if target ~= player:getSummon() then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce so pode evoluir um pokemon seu.")
		return false
	end
	local pokename = target:getName()
	-- pokename = string.gsub(pokename, "Mega ", "")
	if pokename ~= addonnumber[tonumber(item:getSpecialAttribute("addon"))].poke then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Somente o pokemon "..addonnumber[tonumber(item:getSpecialAttribute("addon"))].poke.." pode utilizar esse addon.")
		return false
	end

	if target == player:getSummon() then
		local addonId = item:getSpecialAttribute("addon")
		local addons = player:getUsingBall():getSpecialAttribute("addons") or 0
		if player:getUsingBall():getSpecialAttribute("pokeName"):lower() == "ditto" then
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Ditto nao pode utilizar addons.")
			return true
		end
		if addons ~= 0 then
			player:getUsingBall():setSpecialAttribute("addons", player:getUsingBall():getSpecialAttribute("addons")..""..addonId..",")
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce adicionou o addon "..addonnumber[tonumber(item:getSpecialAttribute("addon"))].poke..".")
			item:remove(1)
			return true
		else
			player:getUsingBall():setSpecialAttribute("addons", ","..addonId..",")
			item:remove(1)
			return true
		end
	end
	return true
end
