local damage = 55
local area = createCombatArea(AREA_CIRCLE2X2)
local area2 = createCombatArea(AREA_SNARL)
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_2X2_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	setConditionOn(creature.uid, target.uid, 'attack minus')
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	local position = creature:getPosition()
	doAreaCombatHealth(creature.uid, COMBAT_DARKDAMAGE, creature:getPosition(), area, damage, damage, 722)
	doAreaCombatHealth(creature.uid, COMBAT_DARKDAMAGE, creature:getPosition(), area2, 0, 0, 722)
	position:getNextPosition(1)
	position:getNextPosition(2)
	position:sendMagicEffect(947)
	return true
end
