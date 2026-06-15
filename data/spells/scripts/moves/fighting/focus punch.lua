local damage = 150

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 232, COMBAT_PHYSICALDAMAGE)
	local condition = Condition(CONDITION_ATTACKPLUS)
	condition:setTicks(5000)
	creature:addCondition(condition)
	return true
end