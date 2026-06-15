local damage = 120/4
local area = createCombatArea(AREA_CIRCLE2X2_2)

local function callBack(creature, damage, times)
	if not Creature(creature) then return true end
	creature = Creature(creature)
	local pos = creature:getPosition()
	doAreaCombatHealth(creature.uid, COMBAT_DRAGONDAMAGE, pos, area, damage, damage, 920, COMBAT_PHYSICALDAMAGE)
	if times == 4 and math.random(1, 3) == 1 then
		setConditionOn(creature.uid, creature.uid, 'confusion')
	end
end

function onCastSpell(creature, variant)
	for i = 0, 4 do
		addEvent(callBack, i * 500, creature.uid, damage, i)
	end
	return true
end
