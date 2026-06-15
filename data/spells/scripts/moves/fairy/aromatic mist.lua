local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)	
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))
combatEvent:setParameter(COMBAT_PARAM_AGGRESSIVE, false)

local condition = Condition(CONDITION_DEFENSEPLUS)
condition:setParameter(CONDITION_PARAM_TICKS, 5000)

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
	target:addCondition(condition)
	target:getPosition():sendMagicEffect(944)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	creature:getPosition():sendMagicEffect(944)
	creature:addCondition(condition)
	return true
end