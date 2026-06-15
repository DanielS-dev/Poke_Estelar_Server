local area = createCombatArea(AREA_MAGMA2)
local areadmg = createCombatArea(AREA_CIRCLE6X6)
local damage = 100	
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	setConditionOn(creature.uid, target.uid, 'burn')
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, 0, 0, 379)
	doAreaCombatHealth(creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), areadmg, damage, damage, 0)
	return true
end
