function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if not hasSummons(player) then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Seu pokemon precisa estar para fora para evoluir.")
		return false
	end
	
	if not isSummon(target) then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce so pode usar isso em um pokemon seu.")
		return false
	end
	
	if target ~= player:getSummon() then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Voce so pode evoluir um pokemon seu.")
		return false
	end
	
	if target:isEvolving() then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Seu pokemon ja esta evoluindo.")
		return false
	end

	local ball = player:getUsingBall()
	if not ball then return false end
	
	local ditto = ball:getSpecialAttribute("pokeName")
	if ditto == "Ditto" then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Seu ditto nao pode evoluir.")
		return false
	end
	
	local summonName = target:getName()
	local monsterType = MonsterType(summonName)
	if not monsterType then
		print("WARNING! Monster " .. summonName .. " with bug on evolution!")
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Esse problema foi reportado aos admins.")
		return false
	end
	local evolutionList = monsterType:getEvolutionList()
	if #evolutionList >= 1 then
		for i = 1, #evolutionList do
			local evolution = evolutionList[i]
			local evolutionName = evolution.name
			if evolutionName ~= "" then
				local levelneeded = evolution.level
				local loveneeded = evolution.love
				player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, loveneeded)
				if loveneeded ~= 0 and ball:getSpecialAttribute("pokeLove") >= loveneeded then
					if summonName == "Eevee" then
						if ball:getSpecialAttribute("pokeLove") >= 75 then
							doEvolveSummon(target:getId(), "Sylveon", false)
							-- player:sendTextMessage(MESSAGE_INFO_DESCR, "Sylveon ainda nao esta liberado.")
							return false
						else
							local worldTime = getWorldTime()
							local hours = math.floor(worldTime / 60)
							if hours > 18 and hours < 6 then
								doEvolveSummon(target:getId(), "Umbreon", false)
								return false
							else
								doEvolveSummon(target:getId(), "Espeon", false)
								return false
							end
						end
					end
					doEvolveSummon(target:getId(), evolutionName, false)
					return false
				end
				if levelneeded ~= 1000 and ball:getSpecialAttribute("pokeLevel") >= levelneeded then
					doEvolveSummon(target:getId(), evolutionName, false)
					return false
				elseif levelneeded ~= 1000 and ball:getSpecialAttribute("pokeLevel") < levelneeded then
					player:sendTextMessage(MESSAGE_INFO_DESCR, "Seu pokemon nao tem o level necessario.")
					return false
				end
			end
		end
	else
		player:sendTextMessage(MESSAGE_INFO_DESCR, "Este pokemon nao evolui.")
		return false
	end
	return false
end
