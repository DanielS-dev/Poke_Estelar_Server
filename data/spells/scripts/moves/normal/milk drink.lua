function onCastSpell(creature, variant)
	doTargetCombatHealth(0, creature.uid, COMBAT_HEALING, creature:getMaxHealth() * 0.50, creature:getMaxHealth() * 0.50, 453)
	return true
end