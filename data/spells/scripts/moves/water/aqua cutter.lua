local area = createCombatArea(AREA_CIRCLE2X2_2)
local damage = 70/2

local function callBack(uid, damage)
	if not Creature(uid) then return true end
	local pos = Creature(uid):getPosition()
	doAreaCombatHealth(uid, COMBAT_WATERDAMAGE, pos, area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	pos.x = pos.x + 2
	pos.y = pos.y + 1
	pos:sendMagicEffect(900)
end

function onCastSpell(creature, variant)
	for i = 0, 1 do
		addEvent(callBack, i * 300, creature.uid, damage)
	end
	return true
end
