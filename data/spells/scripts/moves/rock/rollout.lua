local area = createCombatArea(AREA_CIRCLE1X1)
local damage = 30

local function spellCallback(creature, position, damage)
	if not Creature(creature) then return true end
	local creature = Creature(creature)
	doAreaCombatHealth(creature.uid, COMBAT_ROCKDAMAGE, creature:getPosition(), area, damage, damage, 238, COMBAT_PHYSICALDAMAGE)
end

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	
	for i = 0, 9 do
		if creature:getCondition(CONDITION_DEFENSEPLUS) ~= nil then
			addEvent(spellCallback, i * 500, creature.uid, creature:getPosition(), damage * 2)
		else
			addEvent(spellCallback, i * 500, creature.uid, creature:getPosition(), damage)
		end
	end
	return true
end
