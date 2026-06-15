local foods = {
	[35819] = {6*60*60, 10, "nhac"},
	[35820] = {6*60*60, 15, "nhac"},
	[35821] = {6*60*60, 20, "nhac"},
	[35822] = {24*60*60, 50, "nhac"},
	[35823] = {12*60*60, 15, "nhac"},
	[39201] = {53*60, 2, "crunch"},
	[39222] = {2*60*60, 3, "nhac"},
	
	[35623] = {13*60, 2, "slurp"},
	[35624] = {16*60, 2, "slurp"},
	[35625] = {25*60, 4, "slurp"},
	[35626] = {10*60, 2, "slurp"},
	[35627] = {33*60, 4, "slurp"},
	
	[35629] = {5*60, 1, "glup"},
	[35632] = {36*60, 4, "slurp"},
	[35633] = {53*60, 6, "slurp"},
	
	[39198] = {30, 40, "crunch"},
	[39199] = {9*60*60, 5, "crunch"},
	[39206] = {2*60*60, 4, "nhac"},
	[39207] = {3*60*60, 4, "nhac"},
	[39220] = {60, 70, "munch"},
	[39221] = {2*24*60*60, 20, "..."},
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local food = foods[item:getId()]
	if food == nil then
		return false
	end
	player:feed(food[1], food[2])
	player:say(food[3], TALKTYPE_MONSTER_SAY)
	item:remove(1)
	return true
end