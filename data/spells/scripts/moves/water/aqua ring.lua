function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(815)
	for i = 1, 10 do
		addEvent(doTargetCombatHealth, i * 1000, 0, creature.uid, COMBAT_HEALING, (creature:getMaxHealth() * 0.05), (creature:getMaxHealth() * 0.05), 423)
	end
	return true
end