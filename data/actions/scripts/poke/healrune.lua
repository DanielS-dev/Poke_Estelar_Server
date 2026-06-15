

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local exhaust = Condition(CONDITION_EXHAUST_HEAL)
	if player:isDuelingWithNpc() then
		exhaust:setParameter(CONDITION_PARAM_TICKS, 20000)
	else
		exhaust:setParameter(CONDITION_PARAM_TICKS, 5000)
	end
	
	if player:getCondition(CONDITION_EXHAUST_HEAL) then
		player:sendTextMessage(MESSAGE_STATUS_SMALL, Game.getReturnMessage(RETURNVALUE_YOUAREEXHAUSTED))
		return true
	end

	if player:isOnLeague() then
		if not player:canUsePotionOnLeague() then
			player:sendCancelMessage("Sorry, you can not use potion anymore.")
			player:getPosition():sendMagicEffect(CONST_ME_POFF)
			return true
		end
	end

	local heal = 1
	if item:getId() == 27642 then
		heal = 200
	elseif item:getId() == 27643 then
		heal = 500
	elseif item:getId() == 27641 then
		heal = 750
	elseif item:getId() == 27647 then
		heal = 1000
	elseif item:getId() == 27646 then
		if not player:getSummon() then return false end
		heal = player:getSummon():getMaxHealth() or 0
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
