local damage = 150

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local function doTeleport(bicho, damage)
		creature = Creature(bicho)
		creature:teleportTo(creature:getTarget():getClosestFreePosition(creature:getTarget():getPosition(), 1), false)
		doTargetCombatHealth(creature.uid, creature:getTarget().uid, COMBAT_FIGHTINGDAMAGE, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		local pos = creature:getTarget():getPosition()
		pos.x = pos.x + 3
		pos.y = pos.y + 2
		pos:sendMagicEffect(1013)
	end
	
	for i = 0, 4 do
		addEvent(doSendMagicEffect, i * 500, creature:getPosition(), 920)
	end
	addEvent(doTeleport, 2100, creature.uid, damage)
	return true
end