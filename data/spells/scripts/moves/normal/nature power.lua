function onCastSpell(creature, variant)
	local moves = {"tri attack", "energy ball", "earth power", "power gem", "hydro pump", "ice beam", "lava plume", "air slash", "moonblast", "thunderbolt", "psychic", "draco meteor"}
	doCreatureCastSpell(creature.uid, moves[math.random(1, #moves)])
	return true
end