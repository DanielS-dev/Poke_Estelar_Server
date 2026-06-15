function onStepIn(creature, item, position, fromPosition)

	if not creature:isPlayer() then return false end

	if item.actionid == 102 then
		creature:getPosition():sendMagicEffect(CONST_ME_TELEPORT)
		creature:teleportTo(Position(644, 740, 6))
		creature:getPosition():sendMagicEffect(CONST_ME_TELEPORT)
	end
	return true
end
