function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doSendDistanceShoot(creature:getPosition(), creature:getTarget():getPosition(), 88)
	local target = Creature(creature:getTarget())
	setConditionOn(creature.uid, target.uid, 'confusion')
	return true
end
