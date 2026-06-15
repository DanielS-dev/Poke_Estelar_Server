local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))
combatEvent:setParameter(COMBAT_PARAM_AGGRESSIVE, false)


function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if not isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) and target ~= creature then return false end
			if Player(getPlayerByName(target:getMaster():getName())):isDuelingWithNpc() and target ~= creature then return false end
		elseif target:isPlayer() then
			if not isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) and target ~= creature:getMaster() then return false end
			if Player(getPlayerByName(target:getName())):isDuelingWithNpc() and target ~= creature:getMaster() then return false end
		elseif not target:getMaster() then return false
		end
	else
		if target:getMaster() or target:isPlayer() then return false end
	end
	if target:getCondition(CONDITION_FIRE) ~= nil then
		doRemoveCondition(target.uid, CONDITION_FIRE)
	end
	if target:getCondition(CONDITION_POISON) ~= nil then
		doRemoveCondition(target.uid, CONDITION_POISON)
	end
	if target:getCondition(CONDITION_PARALYZE) ~= nil then
		doRemoveCondition(target.uid, CONDITION_PARALYZE)
	end
	local pos = target:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(814)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	return true
end