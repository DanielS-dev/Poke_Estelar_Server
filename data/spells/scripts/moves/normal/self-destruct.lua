local area = createCombatArea(AREA_CIRCLE3X3)
local damage = 250
function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	local bixo = Creature(creature)
	if creature:getHealth() > 0 then
		if isSummon(creature) then
			bixo:setHealth(0)
			if bixo:getMaster():getUsingBall():setSpecialAttribute("pokeHealth", 0) then
				doAreaCombatHealth(bixo, COMBAT_NORMALDAMAGE, pos, area, damage, damage, 645, COMBAT_PHYSICALDAMAGE)
				doRemoveSummon(bixo:getMaster():getId())
			end
		else
			if bixo:setHealth(0) then
				doAreaCombatHealth(bixo, COMBAT_NORMALDAMAGE, pos, area, damage, damage, 645, COMBAT_PHYSICALDAMAGE)
			end
		end
	end
end
