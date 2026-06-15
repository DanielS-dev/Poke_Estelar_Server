function onCastSpell(creature, variant)
	if not creature:getTarget() then return true end
	if Creature(creature):getMaster() then
		if creature:getCondition(CONDITION_MANASHIELD) ~= nil then
			local moves = MonsterType(creature:getTarget():getName()):getMoveList()
			for i = 1, 10 do
				if creature:getMaster():getUsingBall():getSpecialAttribute("sketch"..tostring(i)) and creature:getMaster():getUsingBall():getSpecialAttribute("sketch"..tostring(i)) ~= 0 and creature:getMaster():getUsingBall():getSpecialAttribute("sketch"..tostring(i)):split("|")[1] == moves[7].name then
					creature:getMaster():sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao pode copiar um ataque que voce ja conhece.")
					return false
				end
			end
			local stg = "" .. moves[7].name .. "|" .. moves[7].speed .. "|" .. moves[7].level .."|" .. moves[7].isTarget .. "|" .. moves[7].range
			creature:getMaster():getUsingBall():setSpecialAttribute("sketch7", stg)
			creature:getPosition():sendMagicEffect(462)
			creature:getMaster():refreshPokemonBar({}, {})
		else
			creature:getMaster():sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Use order no seu smeargle para desbloquear o sketch.")
		end
	else
		local moves = {"bug buzz", "night slash", "dragon claw", "thunderbolt", "moonblast", "aura sphere", "flamethrower", "hurricane", "shadow ball", "solar beam", "earthquake", "aurora beam", "hyper beam", "acid spray", "extrasensory", "rock slide", "meteor mash", "hydro pump"}
		doCreatureCastSpell(creature.uid, moves[math.random(1, #moves)])
	end
	return true
end

