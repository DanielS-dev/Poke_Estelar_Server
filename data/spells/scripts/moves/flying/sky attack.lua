local damage = 140
local area = createCombatArea(AREA_CIRCLE2X2)

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
		setConditionOn(creature.uid, target.uid, 'silence')
	end
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	creature:getPosition():sendMagicEffect(960)
	doHide(creature.uid, true)
	addEvent(doHide, 3000, creature.uid, false)
	local function doDano(creature)
		if not Creature(creature) then return false end
		creature = Creature(creature)
		doAreaCombatHealth(creature.uid, COMBAT_FLYINGDAMAGE, creature:getPosition(), area, damage, damage, 919, COMBAT_PHYSICALDAMAGE)
	end
	addEvent(doDano, 3001, creature.uid)
	return true
end