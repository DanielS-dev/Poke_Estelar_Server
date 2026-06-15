local damage = 40
local area = createCombatArea(AREA_CIRCLE2X2)	

function onCastSpell(creature, variant)
	for i = 0, 3 do
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_BUGDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		local pos = creature:getPosition()
		pos:getNextPosition(1)
		pos:getNextPosition(2)
		pos:sendMagicEffect(1045)
	end
	return true
end

