local damage = 25
local area = createCombatArea(NO_AREA)

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE2X2))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	if math.random(1, 100) <= 10 then
		setConditionOn(creature.uid, target.uid, 'silence')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

local sequence = 
	{
		[1] = {1, -1},
		[2] = {1, 0},
		[3] = {1, 1},
		[4] = {0, 1},
		[5] = {-1, 1},
		[6] = {-1, 0},
		[7] = {-1, -1},
		[8] = {0, -1},
		[9] = {1, -1},
	}

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	for i = 1, 9 do
		local position = creature:getPosition()
		position.x = position.x + sequence[i][1]
		position.y = position.y + sequence[i][2]
		addEvent(doAreaCombatHealth, i * 100, creature.uid, COMBAT_GROUNDDAMAGE, position, area, damage, damage, 237, COMBAT_PHYSICALDAMAGE)
	end
	return true
end
