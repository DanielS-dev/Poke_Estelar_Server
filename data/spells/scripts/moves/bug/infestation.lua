local area = createCombatArea(AREA_CIRCLE2X2)
local damage = 20

local function spellCallback(creature, position)
	if not Creature(creature) then return true end
	local creature = Creature(creature)
	doAreaCombatHealth(creature.uid, COMBAT_BUGDAMAGE, creature:getPosition(), area, damage, damage, 693)
end

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	
	for i = 0, 4 do
		addEvent(spellCallback, i * 500, creature.uid, creature:getPosition())
	end
	return true
end
