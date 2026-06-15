local damage = 300

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	if creature:getTarget():getTotalSpeed() > creature:getTotalSpeed() then
		creature:getPosition():sendMagicEffect(3)
	end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_NORMALDAMAGE, damage, damage, 669, COMBAT_PHYSICALDAMAGE)
	return true
end

