local foods = {
	["mariburger"] = {id = 35819, price = 10000},
	["wobburger"] = {id = 35820, price = 12500},
	["natburger"] = {id = 35821, price = 15000},
	["snorburger"] = {id = 35823, price = 50000},
	["mewburger"] = {id = 35822, price = 100000},
	["french fries"] = {id = 39201, price = 500},
	["pizza"] = {id = 39222, price = 1000},
}

function onSay(player, words, param)
	local food = param:split("|")[1]
	local qt = tonumber(param:split("|")[2])
	local container = player:getSlotItem(CONST_SLOT_BACKPACK)			
	if player:getFreeCapacity() >= 1 and container and container:getEmptySlots() > 0 then
		if player:removeMoney(qt * foods[food].price) then
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Obrigado pela sua compra, voce gastou um total de: $"..qt * foods[food].price.." em "..qt.."x "..firstToUpper(food)..".")
			player:addItem(foods[food].id, qt)
		else
			player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tem dinheiro o suficiente.")
		end
	else
		player:sendTextMessage(MESSAGE_STATUS_CONSOLE_BLUE, "Voce nao tem espaco em seu inventorio.")
	end
	return false
end
