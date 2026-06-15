local damage = 120
local area = createCombatArea(AREA_CIRCLE4X4)

function onCastSpell(creature, variant)
	creature:getPosition():sendMagicEffect(919)
	doHide(creature.uid, true)
	addEvent(doHide, 3000, creature.uid, false)
	local function doDano(creature)
		if not Creature(creature) then return false end
		creature = Creature(creature)
		local pos = creature:getPosition()
		pos:getNextPosition(1)
		pos:getNextPosition(2)
		doAreaCombatHealth(creature.uid, COMBAT_FLYINGDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		doAreaCombatHealth(creature.uid, COMBAT_FLYINGDAMAGE, pos, area, 0, 0, 835, COMBAT_PHYSICALDAMAGE)
	end
	addEvent(doDano, 3001, creature.uid)
	return true
end