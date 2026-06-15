local damage = 80

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_NORMALDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	local pos = creature:getTarget():getPosition()
	pos.x = pos.x + 2
	pos.y = pos.y + 2
	pos:sendMagicEffect(1013)
	return true
end

