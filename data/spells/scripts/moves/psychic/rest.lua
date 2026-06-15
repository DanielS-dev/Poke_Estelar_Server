function onCastSpell(creature, variant)
	setConditionOn(creature, creature, 'sleep')
	addEvent(doTargetCombatHealth, 550, 0, creature.uid, COMBAT_HEALING, creature:getMaxHealth(), creature:getMaxHealth(), 0)
	return true
end