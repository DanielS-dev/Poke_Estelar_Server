function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos:sendMagicEffect(1017)
	addEvent(doTargetCombatHealth, 550, 0, creature.uid, COMBAT_HEALING, (creature:getMaxHealth() * 0.25), (creature:getMaxHealth() * 0.25), 946)
	return true
end