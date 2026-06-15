function onSay(player, words, param)
	if param == "open" then
		local ball = player:getUsingBall() or 0
		if ball ~= 0 then
			local evhp = ball:getSpecialAttribute("evhp") or 0
			local evatk = ball:getSpecialAttribute("evatk") or 0
			local evdef = ball:getSpecialAttribute("evdef") or 0
			local evpoints = ball:getSpecialAttribute("evpoints") or 0
			local evs = {","}
			table.insert(evs, evhp..",")
			table.insert(evs, evatk..",")
			table.insert(evs, evdef..",")
			table.insert(evs, evpoints..",")
			table.insert(evs, ball:getSpecialAttribute("pokeName")..",")
			player:sendExtendedOpcode(65, table.concat(evs))
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Seu pokemon precisa estar pra fora da pokebola.")
			return false
		end
	else
		local ball = player:getUsingBall() or 0
		local pokename = ball:getSpecialAttribute("pokeName") or 0
		local tohp = tonumber(param:split("|")[1])
		local toatk = tonumber(param:split("|")[2])
		local todef = tonumber(param:split("|")[3])
		local topts = tonumber(param:split("|")[4])
		local topoke = param:split("|")[5]
		local evhp = ball:getSpecialAttribute("evhp") or 0
		local evatk = ball:getSpecialAttribute("evatk") or 0
		local evdef = ball:getSpecialAttribute("evdef") or 0
		local evpoints = ball:getSpecialAttribute("evpoints") or 0
		if topoke ~= pokename then
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Esse nao e o mesmo pokemon.")
			return false
		end
		if ball == 0 then
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Seu pokemon precisa estar pra fora da pokebola.")
			return false
		end
		if tohp - evhp > evpoints or toatk - evatk > evpoints or todef - evdef > evpoints then
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tem EV points suficiente.")
			return false
		end
		if tohp > 150 or toatk > 150 or todef > 150 then
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "O limite e 150 por status.")
			return false
		end
		if tohp + toatk + todef > 300 then
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "O maximo de EV Points e 300.")
			return false
		end
		ball:setSpecialAttribute("evhp", tohp)
		ball:setSpecialAttribute("evatk", toatk)
		ball:setSpecialAttribute("evdef", todef)
		ball:setSpecialAttribute("evpoints", topts)
		return false
	end
	return false
end
