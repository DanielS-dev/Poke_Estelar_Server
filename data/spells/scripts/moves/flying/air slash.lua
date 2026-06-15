local area = createCombatArea(AREA_CIRCLE3X3)
local damage = 75/2

function onCastSpell(creature, variant)
	for i = 0, 1 do
		local pos = creature:getPosition()
		addEvent(doAreaCombatHealth, i * 300, creature.uid, COMBAT_FLYINGDAMAGE, creature:getPosition(), area, damage, damage, 0)
		pos.x = pos.x + 2
		pos.y = pos.y + 1
		if creature:getName() == "Scizor" or creature:getName() == "Shiny Scizor" then
			addEvent(doSendMagicEffect, i * 300, pos, 770)
		else
			addEvent(doSendMagicEffect, i * 300, pos, 902)
		end
	end
	return true
end
