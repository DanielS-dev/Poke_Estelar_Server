local area = createCombatArea(AREA_CIRCLE4X4)

function onCastSpell(creature, variant)
	local position = creature:getPosition()
	local positiveCondis = getPositiveConditions(creature)
	local damage = 30 + (30 * #positiveCondis)
	addEvent(doAreaCombatHealth, 750, creature.uid, COMBAT_PSYCHICDAMAGE, creature:getPosition(), area, damage, damage, 962)
	position.x = position.x + 3
	position.y = position.y + 2
	position:sendMagicEffect(975)
	return true
end