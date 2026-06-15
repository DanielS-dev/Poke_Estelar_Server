function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doSendDistanceShoot(creature:getPosition(), creature:getTarget():getPosition(), 155)
	setConditionOn(creature.uid, creature:getTarget().uid, 'confusion')
	return true
end
