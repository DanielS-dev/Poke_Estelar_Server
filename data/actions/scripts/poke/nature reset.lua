function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if hasSummons(player) then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu pokemon precisa estar dentro da pokebola.")
		return false
	end
	
	if not target:isPokeball() then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Voce so pode usar isso em uma pokebola.")
		return false
	end

	if not target:isCreature() then
		if target:isPokeball() then
			local natures = {"Hardy", "Lonely", "Adamant", "Naughty", "Bold", "Docile", "Impish", "Lax", "Modest", "Mild", "Bashful", "Rash", "Calm", "Gentle", "Careful", "Quirky"}
			local nature = target:getSpecialAttribute("nature") or 0
			if nature == 0 then
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Seu pokemon precisa ter uma nature.")
				return true
			end
			local add = nature
			while add == nature do
				add = natures[math.random(1, #natures)]
			end
			target:setSpecialAttribute("nature", add)
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce mudou a nature do seu pokemon.")
			item:remove(1)
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o nature reset em uma pokebola.")
		end
	else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce so pode usar o nature reset em uma pokebola.")
	end
	return true
end
