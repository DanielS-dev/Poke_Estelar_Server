local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)	
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
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_DARKDAMAGE, MonsterType(creature:getName()):getMeleeDamage(), MonsterType(creature:getName()):getMeleeDamage(), 0, COMBAT_PHYSICALDAMAGE)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(833)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	return true
end