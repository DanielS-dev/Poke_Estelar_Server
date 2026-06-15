local area = createCombatArea(AREA_CIRCLE3X3)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE3X3))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	setConditionOn(creature.uid, target.uid, 'defense minus')
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_NORMALDAMAGE, creature:getPosition(), area, 0, 0, 0)
	creature:getPosition():sendMagicEffect(1046)
	return true
end
