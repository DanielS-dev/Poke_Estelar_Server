local transformItems = {
	[3743] = 4404, [4404] = 3743, [39264] = 39265, [39265] = 39264, [39320] = 39321, [39322] = 39323, [39324] = 39325, [39326] = 39327, [39328] = 39329, [39330] = 39331
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local transformIds = transformItems[item:getId()]
	if not transformIds then
		return false
	end

	item:transform(transformIds)
	if isInArray({39265, 39321, 39323, 39325, 39327, 39329, 39331}, item:getId()) then item:decay() end
	return true
end
