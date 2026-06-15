local area = createCombatArea(AREA_CIRCLE2X2)
local damage = 60

function onCastSpell(creature, variant)
	for i = 0, 1 do
		addEvent(doSendMagicEffect, i * 400, Position({x = creature:getPosition().x + 2, y = creature:getPosition().y + 1, z = creature:getPosition().z}), 604) -- East slice
		addEvent(doSendMagicEffect, i * 400, Position({x = creature:getPosition().x + 1, y = creature:getPosition().y + 2, z = creature:getPosition().z}), 603) -- South slice
		addEvent(doSendMagicEffect, i * 400, Position({x = creature:getPosition().x - 1, y = creature:getPosition().y + 1, z = creature:getPosition().z}), 605) -- West slice
		addEvent(doSendMagicEffect, i * 400, Position({x = creature:getPosition().x + 1, y = creature:getPosition().y - 1, z = creature:getPosition().z}), 602) -- North slice
		addEvent(doAreaCombatHealth, i * 400, creature.uid, COMBAT_FIGHTINGDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
