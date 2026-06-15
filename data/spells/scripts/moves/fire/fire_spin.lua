local area = {createCombatArea(AREA_CIRCLE2X2_2)}
local combat = COMBAT_FIREDAMAGE
local damageMultiplier = damageMultiplierMoves.ultimate/5

local function callBack(uid)
	if not Creature(uid) then return true end
	local pos = Creature(uid):getPosition()
	local damage = damageMultiplier * Creature(uid):getTotalMagicAttack()
	doAreaCombatHealth(uid, combat, pos, area[1], -damage, -damage, 16)
end

function onCastSpell(creature, variant)
	for i = 0, 4 do
		addEvent(callBack, i * 500, creature.uid)
	end
	return true
end
