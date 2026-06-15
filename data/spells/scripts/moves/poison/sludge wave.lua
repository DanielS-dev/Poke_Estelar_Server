local area = {createCombatArea(AREA_SOUND1), createCombatArea(AREA_SOUND2), createCombatArea(AREA_SOUND3), createCombatArea(AREA_SOUND4)}
local areadmg = createCombatArea(AREA_CIRCLE4X4)
local damage = 95/4

local combatEvent = Combat()
combatEvent:setArea(createCombatArea(AREA_CIRCLE6X6_CALLBACK))

function onTargetCreature(creature, target)
	if target:isNpc() then return false end
	if creature:getMaster() then
		if target:getMaster() then
			if isInArray(getPartyMembers(creature:getMaster()), Player(getPlayerByName(target:getMaster():getName()))) then return false end
		elseif target:isPlayer() then
			if isInArray(getPartyMembers(creature:getMaster()), getPlayerByName(target:getName())) then return false end
		end
	end
	if math.random(1, 100) <= 30 then
		setConditionOn(creature.uid, target.uid, 'poison')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

local function doWave(creature, i)
	if not Creature(creature) then return true end
	creature = Creature(creature)
	doAreaCombatHealth(creature.uid, COMBAT_POISONDAMAGE, creature:getPosition(), areadmg, damage, damage, 0)
	doAreaCombatHealth(creature.uid, COMBAT_POISONDAMAGE, creature:getPosition(), area[i], 0, 0, 1002)
end

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	for i = 1, #area do
		addEvent(doWave, i * 200, creature.uid, i)
	end
	return true
end