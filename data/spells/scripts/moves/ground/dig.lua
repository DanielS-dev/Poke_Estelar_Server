local damage = 80
local area = createCombatArea(AREA_CIRCLE2X2)

function onCastSpell(creature, variant)
	creature:getPosition():sendMagicEffect(511)
	doHide(creature.uid, true)
	addEvent(doHide, 3000, creature.uid, false)
	local function doDano(creature)
		if not Creature(creature) then return false end
		creature = Creature(creature)
		doAreaCombatHealth(creature.uid, COMBAT_GROUNDDAMAGE, creature:getPosition(), area, damage, damage, 344, COMBAT_PHYSICALDAMAGE)
	end
	addEvent(doDano, 3001, creature.uid)
	return true
end