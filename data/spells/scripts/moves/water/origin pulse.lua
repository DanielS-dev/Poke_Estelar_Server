local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)	
local damage = 110/5
local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))

local function doFire(fromposition, creature, target)
	if not Creature(target) then return false end
	creature = Creature(creature)
	target = Creature(target)
	fromposition:sendMagicEffect(11)
	doSendDistanceShoot(fromposition, Creature(target):getPosition(), 186)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_WATERDAMAGE, damage, damage, 423)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_WATERDAMAGE, 0, 0, 691)
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
	local pos = {
		[1] = {x = creature:getPosition().x, y = creature:getPosition().y - 2, z = creature:getPosition().z},
		[2] = {x = creature:getPosition().x + 2, y = creature:getPosition().y, z = creature:getPosition().z},
		[3] = {x = creature:getPosition().x + 1, y = creature:getPosition().y + 2, z = creature:getPosition().z},
		[4] = {x = creature:getPosition().x - 1, y = creature:getPosition().y + 2, z = creature:getPosition().z},
		[5] = {x = creature:getPosition().x - 2, y = creature:getPosition().y, z = creature:getPosition().z},
	}
	for i = 1, 5 do
		addEvent(doFire, i * 200, Position(pos[i]), creature.uid, target.uid)
	end
	setConditionOn(creature.uid, target.uid, 'attack minus')
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	creature:getPosition():sendMagicEffect(822)
	return true
end