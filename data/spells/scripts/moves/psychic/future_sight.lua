local area = {createCombatArea(AREA_CIRCLE2X2_2)}
local areas = {createCombatArea(AREA_CIRCLE2X2_OUTER1), createCombatArea(AREA_CIRCLE2X2_OUTER2), createCombatArea(AREA_CIRCLE2X2_OUTER3), createCombatArea(AREA_CIRCLE2X2_OUTER4), createCombatArea(AREA_CIRCLE2X2_OUTER5), createCombatArea(AREA_CIRCLE2X2_OUTER6), createCombatArea(AREA_CIRCLE2X2_OUTER7), createCombatArea(AREA_CIRCLE2X2_OUTER8), createCombatArea(AREA_CIRCLE2X2_OUTER1)}

local combat = COMBAT_PSYCHICDAMAGE
local damageMultiplier = damageMultiplierMoves.ultimate/9

local function callBack(uid, pos, damage, times)
	if not Creature(uid) then return true end
	pos = Creature(uid):getPosition()
	doAreaCombatHealth(uid, combat, pos, area[1], -damage, -damage, 720)
	doAreaCombatHealth(uid, combat, pos, areas[times], -damage, -damage, 526)
end

function onCastSpell(creature, variant)
	creature:getPosition():sendMagicEffect()
	for i = 1, 9 do
		local damage = damageMultiplier * creature:getTotalMagicAttack()
		addEvent(callBack, i * 300, creature.uid, pos, damage, i)
	end
	return true
end
