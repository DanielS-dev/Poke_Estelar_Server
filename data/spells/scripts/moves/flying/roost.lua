function onCastSpell(creature, variant)
	setConditionOn(creature, creature, 'burn')
	local heal = creature:getMaxHealth()
	creature:addHealth(heal/2)
	creature:getPosition():sendMagicEffect(949)
	return true
end
