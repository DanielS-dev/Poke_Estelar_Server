local damage = 70

local function doPush(target, pos, creature, i)
	if not Creature(target) then return false end
	if not Creature(creature) then return false end
	target = Creature(target)
	creature = Creature(creature)
	if isInArray({"squirtle turret", "charmander turret", "bulbasaur turret", "caterpie turret", "pikachu turret", "koffing turret", "bellsprout turrent", "porygon turret"}, target:getName():lower()) then return false end
	doSendMagicEffect(Position(pos), 3)
	if isInArray(legendaryPokemons, target:getName()) then return false end
	doTeleportThing(target.uid, Position(pos), true) 
	if i == 3 then
		Creature(creature):getPosition():sendMagicEffect(331)
		addEvent(doTeleportThing, 50, creature.uid, Creature(creature):getClosestFreePosition(Position(pos), 1), true)
	end
end

function onCastSpell(creature, variant)
	if not creature:getTarget() then return false end
	local target = Creature(creature:getTarget())
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	local dir = target:getDirection()
	if dir == 0 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 230, COMBAT_PHYSICALDAMAGE)
		for i = 1, 4 do
			local pos = target:getPosition()
			pos.y = pos.y + i
			addEvent(doPush, i * 50, target.uid, pos, creature.uid, i)
		end
	elseif dir == 1 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 230, COMBAT_PHYSICALDAMAGE)
		for i = 1, 4 do
			local pos = target:getPosition()
			pos.x = pos.x - i
			addEvent(doPush, i * 50, target.uid, pos, creature.uid, i)
		end
	elseif dir == 2 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 230, COMBAT_PHYSICALDAMAGE)
		for i = 1, 4 do
			local pos = target:getPosition()
			pos.y = pos.y - i
			addEvent(doPush, i * 50, target.uid, pos, creature.uid, i)
		end
	elseif dir == 3 then
		doTargetCombatHealth(creature.uid, target.uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 230, COMBAT_PHYSICALDAMAGE)
		for i = 1, 4 do
			local pos = target:getPosition()
			pos.x = pos.x + i
			addEvent(doPush, i * 50, target.uid, pos, creature.uid, i)
		end
	end
	return true
end
