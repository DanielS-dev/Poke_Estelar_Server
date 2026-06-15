local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))
combatEvent:setParameter(COMBAT_PARAM_AGGRESSIVE, false)
local conditions = {Condition(CONDITION_SLEEP), Condition(CONDITION_PARALYZE), Condition(CONDITION_SEED), Condition(CONDITION_SILENCE), Condition(CONDITION_DEFENSEMINUS), Condition(CONDITION_ATTACKMINUS), Condition(CONDITION_FREEZING), Condition(CONDITION_DRUNK), Condition(CONDITION_FIRE), Condition(CONDITION_POISON)}

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
	for i = 1, #conditions do
		if target:getCondition(conditions[i]) ~= nil then
			target:removeCondition(conditions[i])
			target:getPosition():sendMagicEffect(13)
		end
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	return true
end