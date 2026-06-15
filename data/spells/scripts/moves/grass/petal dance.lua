local damage = 120/4
local area = createCombatArea(AREA_CIRCLE2X2_2)

function onCastSpell(creature, variant)
	for i = 0, 4 do
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_GRASSDAMAGE, creature:getPosition(), area, damage, damage, 407)
	end
	
	local function doConfusion(creature)
		setConditionOn(creature, creature, 'confusion')
	end
	if math.random(1, 3) == 1 then
		addEvent(doConfusion, 2000, creature.uid)
	end
	return true
end
