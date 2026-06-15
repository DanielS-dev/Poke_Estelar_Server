local exhaust = Condition(CONDITION_EXHAUST_HEAL)
exhaust:setParameter(CONDITION_PARAM_TICKS, 5000)

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	
	if player:getCondition(CONDITION_EXHAUST_HEAL) then
		player:sendTextMessage(MESSAGE_STATUS_SMALL, Game.getReturnMessage(RETURNVALUE_YOUAREEXHAUSTED))
		return true
	end
	
	if player:isDuelingWithNpc() then
		player:sendCancelMessage("Sorry, not possible while in duels.")
		player:getPosition():sendMagicEffect(CONST_ME_POFF)
		return true
	end

	if player:isOnLeague() then
		if not player:canUsePotionOnLeague() then
			player:sendCancelMessage("Sorry, you can not use potion anymore.")
			player:getPosition():sendMagicEffect(CONST_ME_POFF)
			return true
		end
	end
	
	if player:getSummon() then
		player:getSummon():addHealth(heal)
		player:getSummon():getPosition():sendMagicEffect(CONST_ME_MAGIC_GREEN)
		player:addCondition(exhaust)
	else
		player:sendCancelMessage("Sorry, you can only use potions on pokemons.")
		player:getPosition():sendMagicEffect(CONST_ME_POFF)
		return true
	end
	item:remove(1)
	return true
end
