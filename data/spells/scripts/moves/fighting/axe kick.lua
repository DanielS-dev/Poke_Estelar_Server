local damage = 120

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	local pos = creature:getTarget():getPosition()
	pos:getNextPosition(1)
	pos:sendMagicEffect(621)
	if math.random(1, 100) <= 30 then
		setConditionOn(creature.uid, creature:getTarget().uid, 'confusion')
	end
	return true
end