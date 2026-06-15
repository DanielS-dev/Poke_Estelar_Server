local damage = 70

function onCastSpell(creature, variant)
	if not creature:getTarget() then return false end
	local target = creature:getTarget()
	local pos = target:getPosition()
	pos:getNextPosition(1)
	pos:sendMagicEffect(497)
	if target:getCondition(CONDITION_PARALYZE) ~= nil then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, damage * 2, damage * 2, 0, COMBAT_PHYSICALDAMAGE)
		target:removeCondition(CONDITION_PARALYZE)
	else
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
