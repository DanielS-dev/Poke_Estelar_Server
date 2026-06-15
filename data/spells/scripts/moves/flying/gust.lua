local damage = 40
local area = createCombatArea(NO_AREA)

local sequence = 
	{
		[1] = {1, -1},
		[2] = {1, 0},
		[3] = {1, 1},
		[4] = {0, 1},
		[5] = {-1, 1},
		[6] = {-1, 0},
		[7] = {-1, -1},
		[8] = {0, -1},
		[9] = {1, -1},
	}

local function spellCallback(uid, damage, count, posNumber)
	if not Creature(uid) then return true end
	local creature = Creature(uid)
	if creature then		
		if count <= 1 then
			local position = creature:getPosition()
			position.x = position.x + sequence[posNumber][1]
			position.y = position.y + sequence[posNumber][2]
			doAreaCombatHealth(uid, COMBAT_FLYINGDAMAGE, position, area, damage, damage, 550)
			posNumber = posNumber + 1
			if posNumber > #sequence then
				count = count + 1
				posNumber = 1
			end
			addEvent(spellCallback, 100, uid, damage, count, posNumber)
		end
	end
end

function onCastSpell(creature, variant)
	spellCallback(creature.uid, damage, 1, 1)
	return true
end
