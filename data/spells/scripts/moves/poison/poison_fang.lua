local damageMultiplier = damageMultiplierMoves.singletargetweak
local missileEffect = 5
local areaEffect = 687
local area = createCombatArea(AREA_BEAM1)
local combat = COMBAT_POISONDAMAGE

function onCastSpell(creature, variant)
	local damage = damageMultiplier * creature:getTotalMagicAttack()
	local pid = Game.getSpectators(creature:getPosition(), false, false, 0, 3, 0, 3)
	if pid and #pid > 0 then
        for i = 1, #pid do
            if not pid[i]:isPlayer() and not pid[i]:isNpc() and not isSummon(pid[i]) then
				local wild = Creature(pid[i])
				local poison = Condition(CONDITION_POISON)
				poison:setParameter(CONDITION_PARAM_DELAYED, true)
				poison:addDamage(5, 1000, -math.random(400, 500))
				doTargetCombatHealth(creature.uid, wild, combat, -damage, -damage, areaEffect)
				wild:getPosition():sendMagicEffect(258)
				if math.random(1, 100) <= 50 then
					wild:addCondition(poison)
				end
			end
		end
	end
	return true
end
