local function doFirst(creature, target)
	creature = Creature(creature)
	target = Creature(target)
	if isInArray({"Ditto", "Shiny Ditto", "Smeargle", "Shiny Smeargle"}, target:getName()) then return false end
	local moves = MonsterType(target:getName()):getMoveList()
	local slot = math.random(1, #moves)
	doCreatureCastSpell(creature.uid, moves[slot].name)
end

function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	local pos = creature:getPosition()
	pos:getNextPosition(0)
	pos:sendMagicEffect(281)
	doFirst(creature.uid, creature:getTarget())
	return true
end

