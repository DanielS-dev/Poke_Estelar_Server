function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local target = creature:getTarget()
	local maxhealth = target:getMaxHealth() / 100
	local health = target:getHealth()
	if health > maxhealth * 70 and health <= maxhealth * 100 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, 20, 20, 231, COMBAT_PHYSICALDAMAGE)
	elseif health > maxhealth * 35 and health <= maxhealth * 70 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, 40, 40, 231, COMBAT_PHYSICALDAMAGE)
	elseif health > maxhealth * 20 and health <= maxhealth * 35 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, 80, 80, 231, COMBAT_PHYSICALDAMAGE)
	elseif health > maxhealth * 10 and health <= maxhealth * 20 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, 100, 100, 231, COMBAT_PHYSICALDAMAGE)
	elseif health > maxhealth * 4 and health <= maxhealth * 10 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, 150, 150, 231, COMBAT_PHYSICALDAMAGE)
	elseif health > 0 and health <= maxhealth * 4 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, 200, 200, 231, COMBAT_PHYSICALDAMAGE)
	end
	return true
end