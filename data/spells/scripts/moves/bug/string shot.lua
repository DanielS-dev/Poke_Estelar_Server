function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doSendDistanceShoot(creature:getPosition(), creature:getTarget():getPosition(), 80)
	setConditionOn(creature.uid, creature:getTarget().uid, 'slow')
	creature:getTarget():getPosition():sendMagicEffect(257)
	return true
end
