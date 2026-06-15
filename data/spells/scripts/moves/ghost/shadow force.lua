local damage = 120
local area = createCombatArea(AREA_CIRCLE2X2)

function onCastSpell(creature, variant)
	local pos = creature:getPosition()
	pos:getNextPosition(1)
	pos:sendMagicEffect(535)
	doHide(creature.uid, true)
	addEvent(doHide, 3000, creature.uid, false)
	local pos = creature:getPosition()
	local pos2 = creature:getPosition()
	pos2:getNextPosition(1)
	addEvent(doSendMagicEffect, 3000, pos2, 536)
	for i = 1, 100 do
		local place = {x = pos.x + math.random(-4, 4), y = pos.y + math.random(-3, 3), z = pos.z}
		if math.random(1, 3) == 1 then
			place.x = place.x + 1
			place.y = place.y + 1
			addEvent(doSendMagicEffect, 3000 + (i * 10), place, 421)
		end
	end
	local function doDano(creature)
		if not Creature(creature) then return false end
		creature = Creature(creature)
		doAreaCombatHealth(creature.uid, COMBAT_GHOSTDAMAGE, creature:getPosition(), area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
	end
	addEvent(doDano, 3250, creature.uid)
	return true
end