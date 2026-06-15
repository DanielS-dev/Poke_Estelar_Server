local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 100/5

function onCastSpell(creature, variant)
	local function doEff(creature)
		if not Creature(creature) then return false end
		creature = Creature(creature)
		local pos = creature:getPosition()
		pos.x = pos.x + 3
		pos.y = pos.y + 2
		pos:sendMagicEffect(971)
	end
	for i = 0, 4 do
		addEvent(doAreaCombatHealth, i * 500, creature.uid, COMBAT_DARKDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		addEvent(doEff, i * 500, creature.uid)
	end
	return true
end
