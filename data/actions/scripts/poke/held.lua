local helds = {
	['held attack'] = {36473}, -- Aumenta o ataque em porcentagem. 5/10
	['held defense'] = {36472}, -- Aumenta a defesa em porcentagem. 5/10
	['held experience'] = {36474}, -- Aumenta a experiencia em porcentagem. 25/50
	['held burn'] = {36475}, -- Aumenta o dano do burn. 2/3
	['held poison'] = {36488}, -- Aumenta o dano do poison. 2/3
	['held vitality'] = {36479}, -- Aumenta a vida em porcentagem. 25/50
	['held wing'] = {36489}, -- Aumenta a velocidade de voo. 150/300
	["king's rock"] = {26746},
	['metal coat'] = {26747},
	['dragon scale'] = {26743},
	['upgrade'] = {38940},
	['dubious disk'] = {38937},
	['protector'] = {38939},
	['electirizer'] = {27684},
	['magmarizer'] = {27738},
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
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
	
	if player:getUsingBall():getSpecialAttribute("held") and player:getUsingBall():getSpecialAttribute("held") ~= 0 then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Seu pokemon ja possui um held, remova o held para adicionar outro.")
		return false
	end

	if target == player:getSummon() then
		if helds[item:getName():lower()] then
			local heldName = item:getName():lower()
			local heldTier = item:getId()
			if player:getUsingBall():setSpecialAttribute("held", heldName) then
				item:remove()
				return false
			end
		else
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "Held desabilitado no momento, por favor informe a equipe sobre o held.")
			return false
		end
	end
	return true
end
