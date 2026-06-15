local damage = 90/10

local area = createCombatArea(AREA_CIRCLE3X3)	
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_3X3_CALLBACK))

local function doDoom(creature, target, times)
	if not creature then return false end
	if not target then return false end
	target = Creature(target)
	creature = Creature(creature)
	local pos = {x = target:getPosition().x + math.random(-2, 2), y = target:getPosition().y + math.random(-2, 2), z = target:getPosition().z}
	doSendDistanceShoot(Position(pos), target:getPosition(), 196)
	addEvent(doTargetCombatHealth, times * 25, creature.uid, target.uid, COMBAT_BUGDAMAGE, damage, damage, 693, COMBAT_PHYSICALDAMAGE)
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
		addEvent(doDoom, 250 + (i * 50), creature.uid, target.uid, i)
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, 0, 0, 0)
	local pos = creature:getPosition()
	pos.x = pos.x + 1
	pos.y = pos.y + 1
	pos:sendMagicEffect(947)
	return true
end
