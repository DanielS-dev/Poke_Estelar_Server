local damage = 90
local area = createCombatArea(AREA_CIRCLE3X3)

function onCastSpell(creature, variant)
	local dano = COMBAT_NORMALDAMAGE
	if creature:getName() == "Primarina" then
		dano = COMBAT_WATERDAMAGE
	end
	doAreaCombatHealth(creature.uid, dano, creature:getPosition(), area, damage, damage, 25)
	return true
end
