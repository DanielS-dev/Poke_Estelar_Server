local cleanMapAtServerSave = true

local function serverSave()
	-- cleanMap()
	saveServer()
end

function onThink(interval)
	broadcastMessage("Servidor esta sendo salvo, pode travar levemente.", MESSAGE_STATUS_WARNING)
	addEvent(serverSave, 60000)
	return true
end
