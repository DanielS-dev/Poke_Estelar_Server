local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND4)}
local areadmg = createCombatArea(AREA_CIRCLE4X4)
local damage = 100/4

local function spellCallback(uid, position, damage, count, pos2)
	local creature = Creature(uid)
	if creature then		
		if count <= #area then
			doAreaCombatHealth(uid, COMBAT_GROUNDDAMAGE, position, areadmg, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
			doAreaCombatHealth(uid, COMBAT_GROUNDDAMAGE, pos2, area[count], 0, 0, 754)
			count = count + 1			
			addEvent(spellCallback, 500, uid, position, damage, count, pos2)
		end
	end
end

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	for i = 1, #area do
		addEvent(doAreaCombatHealth, (i - 1) * 300, creature.uid, COMBAT_GROUNDDAMAGE, creature:getPosition(), areadmg, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		addEvent(doAreaCombatHealth, (i - 1) * 300, creature.uid, COMBAT_GROUNDDAMAGE, pos, area[i], 0, 0, 754)
	end
	return true
end
