local time = 10000
local effect = 773
local damageMultiplier = damageMultiplierMoves.areawaves/(time/2000.0)
local conditionType = CONDITION_POISON

local combat = Combat()
combat:setParameter(COMBAT_PARAM_EFFECT, effect)
combat:setArea(createCombatArea(AREA_CIRCLE3X3))

function onCastSpell(creature, variant, isHotkey)

	local damage = damageMultiplier * creature:getTotalMagicAttack()
	
	if creature:isPokemon() then
		
		local heldx = creature:getMaster():getUsingBall():getSpecialAttribute("heldx") or 0
		if heldx ~= 0 then
			if firstToUpper(heldx:split("|")[1]) == "Poison" then damage = damage * 10 end
		end
		
	end

	local condition = Condition(conditionType)
	condition:setParameter(CONDITION_PARAM_PERIODICDAMAGE, -damage)
	condition:setParameter(CONDITION_PARAM_TICKS, time)
	condition:setParameter(CONDITION_PARAM_SPEED, -1000)
	combat:setCondition(condition)

	if not combat:execute(creature, variant) then
		return false
	end

	return true
end
