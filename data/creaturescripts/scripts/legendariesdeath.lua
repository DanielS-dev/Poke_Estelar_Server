function onPrepareDeath(creature, killer)
	for cid, _ in pairs(creature:getDamageMap()) do
		local player = Player(cid)
		if player then
			player:setKilledLegendaryPokemon()
		end
	end
	return true
end