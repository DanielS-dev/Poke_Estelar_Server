local damage = 70
local area = createCombatArea(AREATRIPLE_BEAM1)

function onCastSpell(creature, variant)
	local position = creature:getPosition()
	local dir = creature:getDirection()
	local pos = creature:getPosition()
	position:getNextPosition(dir)
	if dir == 0 then
		doAreaCombatHealth(creature.uid, COMBAT_STEELDAMAGE, position, area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		pos.x = pos.x + 1
		pos.y = pos.y - 1
		pos:sendMagicEffect(602)
	elseif dir == 1 then
		doAreaCombatHealth(creature.uid, COMBAT_STEELDAMAGE, position, area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		pos.x = pos.x + 2
		pos.y = pos.y + 1
		pos:sendMagicEffect(604)
	elseif dir == 2 then
		doAreaCombatHealth(creature.uid, COMBAT_STEELDAMAGE, position, area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		pos.x = pos.x + 1
		pos.y = pos.y + 2
		pos:sendMagicEffect(603)
	elseif dir == 3 then
		doAreaCombatHealth(creature.uid, COMBAT_STEELDAMAGE, position, area, damage, damage, 0, COMBAT_PHYSICALDAMAGE)
		pos.x = pos.x - 1
		pos.y = pos.y + 1
		pos:sendMagicEffect(605)
	end
	return true
end
