function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local damage = creature:getHealth() / creature:getMaxHealth()
	if damage <= 0.0417 then
		damage = 200
	elseif damage <= 0.0938 then
		damage = 150
	elseif damage <= 0.2031 then
		damage = 100
	elseif damage <= 0.3438 then
		damage = 80
	elseif damage <= 0.6719 then
		damage = 40
	elseif damage <= 1 then
		damage = 20
	end
	doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_NORMALDAMAGE, damage, damage, 230, COMBAT_PHYSICALDAMAGE)
	return true
end

