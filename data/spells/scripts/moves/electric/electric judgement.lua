local damage = 200/3

local area = createCombatArea(AREA_CIRCLE3X3)	
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_3X3_CALLBACK))

local function doDoom(creature, target, times)
	if not Creature(creature) then return false end
	if not Creature(target) then return false end
	target = Creature(target)
	creature = Creature(creature)
	local pos = {x = target:getPosition().x - math.random(2, 8), y = target:getPosition().y - 6, z = target:getPosition().z}
	doSendDistanceShoot(Position(pos), target:getPosition(), 140)
	if math.fmod(times, 4) == 0 then
		addEvent(doTargetCombatHealth, times * 100, creature.uid, target.uid, COMBAT_ELECTRICDAMAGE, damage, damage, 0)
		local pos2 = target:getPosition()
		pos2:getNextPosition(1)
		pos2:getNextPosition(2)
		pos2:sendMagicEffect(1051)
	end
end
function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	for i = 0, 9 do
		addEvent(doDoom, i * 50, creature.uid, target.uid, i)
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, 0, 0, 0)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(814)
	return true
end
