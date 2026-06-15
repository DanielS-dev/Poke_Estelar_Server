function onCastSpell(creature, variant)
	addEvent(doTargetCombatHealth, 550, 0, creature.uid, COMBAT_HEALING, creature:getMaxHealth() * 0.25, creature:getMaxHealth() * 0.25, 606)
	return true
end