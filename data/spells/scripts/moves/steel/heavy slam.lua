local area = createCombatArea(AREA_CIRCLE2X2)

function onCastSpell(creature, variant)
	local damage = 40
	if isInArray(weight.superheavy, creature:getName()) then
		damage = 120
	elseif isInArray(weight.heavy, creature:getName()) then
		damage = 100
	elseif isInArray(weight.normal, creature:getName()) then
		damage = 80
	end
	doAreaCombatHealth(creature.uid, COMBAT_STEELDAMAGE, creature:getPosition(), area, damage, damage, 10, COMBAT_PHYSICALDAMAGE)
	return true
end
