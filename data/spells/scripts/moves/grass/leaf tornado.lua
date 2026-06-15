local damage = 65/3
local area = createCombatArea(AREA_CIRCLE6X6)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-6, 6), y = pos.y + math.random(-5, 5), z = pos.z}
		if math.random(1, 2) == 1 then
			place.x = place.x + 1
			addEvent(doSendMagicEffect, i * 10, place, 849)
		end
	end
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(850)
	addEvent(doAreaCombatHealth, 250, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 500, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0)
	addEvent(doAreaCombatHealth, 750, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 0)
	if not isInArray(hiddenabilities.clearbody, creature:getName()) then
		setConditionOn(creature, creature, 'attack minus')
	end
	return true
end