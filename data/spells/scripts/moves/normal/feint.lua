local damage = 30

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	if creature:getTarget():getCondition(Condition(CONDITION_IMMUNE)) ~= nil then
		creature:getTarget():removeCondition(Condition(CONDITION_IMMUNE))
	end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_NORMALDAMAGE, damage, damage, 231, COMBAT_PHYSICALDAMAGE)
	return true
end

