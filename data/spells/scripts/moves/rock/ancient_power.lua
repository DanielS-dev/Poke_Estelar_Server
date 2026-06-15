local damage = 50

local function callBack(creature, target, damage)
	if not Creature(creature) then return true end
	creature = Creature(creature)
	target = Creature(target)
	local topos = target:getClosestFreePosition(target:getPosition(), 1)
	local frompos = creature:getPosition()
	frompos:sendMagicEffect(920)
	creature:teleportTo(topos, false)
	doTargetCombatHealth(creature.uid, target, COMBAT_FIREDAMAGE, damage, damage, 16, COMBAT_PHYSICALDAMAGE)
end

function onCastSpell(creature, variant)
	local pid = Game.getSpectators(creature:getPosition(), false, false, 0, 5, 0, 5)
	local pos = creature:getPosition()
	
	local function tpmeback(creature, pos)
		creature = Creature(creature)
		creature:getPosition():sendMagicEffect(920)
		creature:teleportTo(Position(pos), true)
	end
	
	if pid and #pid > 0 then
        for i = 1, #pid do
            if not pid[i]:isPlayer() and not pid[i]:isNpc() and not isSummon(pid[i]) then
				local target = Creature(pid[i])
				local condition = Condition(CONDITION_HASTE)
				condition:setParameter(CONDITION_PARAM_TICKS, 5000)
				condition:setFormula(0, target:getSpeed(), 0, target:getSpeed())
				creature:addCondition(condition)
				addEvent(callBack, (i - 1) * 210, creature.uid, target.uid, damage)
				if i >= #pid then
					addEvent(tpmeback, i * 220, creature.uid, pos)
				end
			end
		end
	end
	
	
	
	return true
end