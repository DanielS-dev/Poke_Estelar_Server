local damage = 75

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_NORMALDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	local pos = creature:getTarget():getPosition()
	pos:getNextPosition(1)
	pos:getNextPosition(2)
	pos:sendMagicEffect(816)
	if math.random(1, 2) == 1 then
		setConditionOn(creature.uid, creature:getTarget().uid, 'defense minus')
	end
	return true
end

