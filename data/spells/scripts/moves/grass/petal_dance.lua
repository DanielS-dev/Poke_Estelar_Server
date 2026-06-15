local area = createCombatArea(AREA_CIRCLE2X2_2)
local combat = COMBAT_GRASSDAMAGE
local damage = 120/4

local function callBack(uid, pos, damage)
	if not Creature(uid) then return true end
	uid = Creature(uid)
	local pos = uid:getPosition()
	doAreaCombatHealth(uid, combat, pos, area, damage, damage, 407)
end

function onCastSpell(creature, variant)
	for i = 0, 4 do
		
		addEvent(callBack, i * 500, creature.uid, pos, damage)
	end
	local confusion = Condition(CONDITION_DRUNK)
	confusion:setParameter(CONDITION_PARAM_TICKS, 4000)
	creature:addCondition(confusion)
	return true
end
