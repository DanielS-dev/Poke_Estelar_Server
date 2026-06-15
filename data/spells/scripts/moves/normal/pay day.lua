local damage = 40

local area = createCombatArea(AREA_CIRCLE6X6_CALLBACK)	
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
		if not getTileInfo(getThingPos(creature.uid)).pvp then
			if math.random(1, 100) <= 5 then
				creature:getMaster():addItem(2148, math.random(25, 50))
			else
				creature:getMaster():addItem(2148, math.random(1, 3))
			end
		end
	end
	doSendDistanceShoot(creature:getPosition(), target:getPosition(), 197)
	doTargetCombatHealth(creature.uid, target.uid, COMBAT_NORMALDAMAGE, damage, damage, 29, COMBAT_PHYSICALDAMAGE)
end

combatEvent:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	combatEvent:execute(creature, variant)
	doAreaCombatHealth(creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, 0, 0, 0)
	creature:getPosition():sendMagicEffect(290)
	return true
end
