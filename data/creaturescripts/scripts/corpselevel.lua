function onDeath(creature, corpse, killer, mostDamage, unjustified, mostDamage_unjustified)
	if type(corpse) ~= "userdata" then
		return true
	end
	if corpse and creature and MonsterType(creature:getName()):getCorpseId() ~= 0 and not isSummon(creature) then
		local level = creature:getLevel()
		if level then
			corpse:setSpecialAttribute("corpseLevel", level)
		else
			print("WARNING! Creature " .. creature:getName() .. " not possible to set corpse level!")
		end
		if creature:getName() == "Unown" then
			local letter = creature:getOutfit().lookType or 0
			corpse:setSpecialAttribute("unown", getUnownKey(letter))
		elseif creature:getName() == "Wormadam" then
			local typeworm = creature:getOutfit().lookType or 0
			corpse:setSpecialAttribute("wormadam", typeworm)
		end
		if creature:getSkull() >= 11 and creature:getSkull() <= 28 then
			corpse:setSpecialAttribute("teraType", creature:getSkull())
			for i = 1, 10 do
				addEvent(doSendMagicEffect, i * 1000, corpse:getPosition(), 57)
			end
			Game.sendAnimatedText(corpse:getPosition(), "TERA", TEXTCOLOR_LIGHTAQUA)
		end
	end
	return true
end
