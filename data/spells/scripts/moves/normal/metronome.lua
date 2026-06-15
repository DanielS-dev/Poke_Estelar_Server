function onCastSpell(creature, variant)
	local moves = {"bug buzz", "night slash", "dragon claw", "thunderbolt", "moonblast", "aura sphere", "flamethrower", "hurricane", "shadow ball", "solar beam", "earthquake", "aurora beam", "hyper beam", "acid spray", "extrasensory", "rock slide", "meteor mash", "hydro pump"}
	doCreatureCastSpell(creature.uid, moves[math.random(1, #moves)])
	return true
end