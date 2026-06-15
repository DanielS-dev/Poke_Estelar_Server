local damage = 75

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	if creature:getTarget():getCondition(CONDITION_IMMUNE) ~= nil then
		creature:getTarget():removeCondition(CONDITION_IMMUNE)
	end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 563, COMBAT_PHYSICALDAMAGE)
	return true
end

