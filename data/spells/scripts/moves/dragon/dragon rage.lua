function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local target = Creature(creature:getTarget())
	doSendDistanceShoot(creature:getPosition(), creature:getTarget():getPosition(), 186)
	target:getPosition():sendMagicEffect(354)
	target:addHealth(-400)
	return true
end
