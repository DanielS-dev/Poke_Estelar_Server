local damage = 110/3
local area = createCombatArea(AREA_CIRCLE6X6)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE2X2))

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
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendMagicEffect, 1000 + (i * 10), place, 904)
		end
	end
	combatEvent:execute(creature, variant)
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(904)
	addEvent(doAreaCombatHealth, 800, creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1100, creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 1400, creature.uid, COMBAT_FIREDAMAGE, creature:getPosition(), area, damage, damage, 0)
	return true
end