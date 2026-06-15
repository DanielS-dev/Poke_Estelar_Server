local doors = {
	[101] = {centerpos = {x=1111,y=1664,z=15}, enterpos = {x=1114,y=1664,z=15}, leavepos = {x=1116,y=1664,z=15}},
	[102] = {centerpos = {x=1124,y=1656,z=15}, enterpos = {x=1124,y=1659,z=15}, leavepos = {x=1124,y=1661,z=15}},
	[103] = {centerpos = {x=1124,y=1671,z=15}, enterpos = {x=1124,y=1668,z=15}, leavepos = {x=1124,y=1666,z=15}},
	[104] = {centerpos = {x=1136,y=1671,z=15}, enterpos = {x=1136,y=1668,z=15}, leavepos = {x=1136,y=1666,z=15}},
	[105] = {centerpos = {x=1136,y=1656,z=15}, enterpos = {x=1136,y=1659,z=15}, leavepos = {x=1136,y=1661,z=15}},
	[106] = {centerpos = {x=1148,y=1671,z=15}, enterpos = {x=1148,y=1668,z=15}, leavepos = {x=1148,y=1666,z=15}},
	[107] = {centerpos = {x=1148,y=1656,z=15}, enterpos = {x=1148,y=1659,z=15}, leavepos = {x=1148,y=1661,z=15}},
	[108] = {centerpos = {x=1160,y=1671,z=15}, enterpos = {x=1160,y=1668,z=15}, leavepos = {x=1160,y=1666,z=15}},
	[109] = {centerpos = {x=1160,y=1656,z=15}, enterpos = {x=1160,y=1659,z=15}, leavepos = {x=1160,y=1661,z=15}},
	[110] = {centerpos = {x=1172,y=1671,z=15}, enterpos = {x=1172,y=1668,z=15}, leavepos = {x=1172,y=1666,z=15}},
	[111] = {centerpos = {x=1172,y=1656,z=15}, enterpos = {x=1172,y=1659,z=15}, leavepos = {x=1172,y=1661,z=15}},
	[112] = {centerpos = {x=1184,y=1671,z=15}, enterpos = {x=1184,y=1668,z=15}, leavepos = {x=1184,y=1666,z=15}},
	[113] = {centerpos = {x=1184,y=1656,z=15}, enterpos = {x=1184,y=1659,z=15}, leavepos = {x=1184,y=1661,z=15}},
	[114] = {centerpos = {x=1196,y=1671,z=15}, enterpos = {x=1196,y=1668,z=15}, leavepos = {x=1196,y=1666,z=15}},
	[115] = {centerpos = {x=1196,y=1656,z=15}, enterpos = {x=1196,y=1659,z=15}, leavepos = {x=1196,y=1661,z=15}},
	[116] = {centerpos = {x=1201,y=1682,z=15}, enterpos = {x=1204,y=1682,z=15}, leavepos = {x=1206,y=1682,z=15}},
	[117] = {centerpos = {x=1217,y=1682,z=15}, enterpos = {x=1214,y=1682,z=15}, leavepos = {x=1212,y=1682,z=15}},
	[118] = {centerpos = {x=1201,y=1693,z=15}, enterpos = {x=1204,y=1693,z=15}, leavepos = {x=1206,y=1693,z=15}},
	[119] = {centerpos = {x=1217,y=1693,z=15}, enterpos = {x=1214,y=1693,z=15}, leavepos = {x=1212,y=1693,z=15}},
	[120] = {centerpos = {x=1201,y=1704,z=15}, enterpos = {x=1204,y=1704,z=15}, leavepos = {x=1206,y=1704,z=15}},
	[121] = {centerpos = {x=1217,y=1704,z=15}, enterpos = {x=1214,y=1704,z=15}, leavepos = {x=1212,y=1704,z=15}},
	[122] = {centerpos = {x=1209,y=1714,z=15}, enterpos = {x=1209,y=1711,z=15}, leavepos = {x=1209,y=1709,z=15}},
	[123] = {centerpos = {x=1222,y=1656,z=15}, enterpos = {x=1222,y=1659,z=15}, leavepos = {x=1222,y=1661,z=15}},
	[124] = {centerpos = {x=1222,y=1671,z=15}, enterpos = {x=1222,y=1668,z=15}, leavepos = {x=1222,y=1666,z=15}},
	[125] = {centerpos = {x=1234,y=1656,z=15}, enterpos = {x=1234,y=1659,z=15}, leavepos = {x=1234,y=1661,z=15}},
	[126] = {centerpos = {x=1234,y=1671,z=15}, enterpos = {x=1234,y=1668,z=15}, leavepos = {x=1234,y=1666,z=15}},
	[127] = {centerpos = {x=1246,y=1671,z=15}, enterpos = {x=1246,y=1668,z=15}, leavepos = {x=1246,y=1666,z=15}},
	[128] = {centerpos = {x=1246,y=1656,z=15}, enterpos = {x=1246,y=1659,z=15}, leavepos = {x=1246,y=1661,z=15}},
	[129] = {centerpos = {x=1258,y=1671,z=15}, enterpos = {x=1258,y=1668,z=15}, leavepos = {x=1258,y=1666,z=15}},
	[130] = {centerpos = {x=1258,y=1656,z=15}, enterpos = {x=1258,y=1659,z=15}, leavepos = {x=1258,y=1661,z=15}},
	[131] = {centerpos = {x=1270,y=1671,z=15}, enterpos = {x=1270,y=1668,z=15}, leavepos = {x=1270,y=1666,z=15}},
	[132] = {centerpos = {x=1270,y=1656,z=15}, enterpos = {x=1270,y=1659,z=15}, leavepos = {x=1270,y=1661,z=15}},
	[133] = {centerpos = {x=1282,y=1671,z=15}, enterpos = {x=1282,y=1668,z=15}, leavepos = {x=1282,y=1666,z=15}},
	[134] = {centerpos = {x=1282,y=1656,z=15}, enterpos = {x=1282,y=1659,z=15}, leavepos = {x=1282,y=1661,z=15}},
	[135] = {centerpos = {x=1294,y=1671,z=15}, enterpos = {x=1294,y=1668,z=15}, leavepos = {x=1294,y=1666,z=15}},
	[136] = {centerpos = {x=1294,y=1656,z=15}, enterpos = {x=1294,y=1659,z=15}, leavepos = {x=1294,y=1661,z=15}},
	[137] = {centerpos = {x=1201,y=1645,z=15}, enterpos = {x=1204,y=1645,z=15}, leavepos = {x=1206,y=1645,z=15}},
	[138] = {centerpos = {x=1217,y=1645,z=15}, enterpos = {x=1214,y=1645,z=15}, leavepos = {x=1212,y=1645,z=15}},
	[139] = {centerpos = {x=1217,y=1634,z=15}, enterpos = {x=1214,y=1634,z=15}, leavepos = {x=1212,y=1634,z=15}},
	[140] = {centerpos = {x=1201,y=1634,z=15}, enterpos = {x=1204,y=1634,z=15}, leavepos = {x=1206,y=1634,z=15}},
	[141] = {centerpos = {x=1217,y=1623,z=15}, enterpos = {x=1214,y=1623,z=15}, leavepos = {x=1212,y=1623,z=15}},
	[142] = {centerpos = {x=1201,y=1623,z=15}, enterpos = {x=1204,y=1623,z=15}, leavepos = {x=1206,y=1623,z=15}},
	[143] = {centerpos = {x=1209,y=1613,z=15}, enterpos = {x=1209,y=1616,z=15}, leavepos = {x=1209,y=1618,z=15}},
	[144] = {centerpos = {x=1306,y=1664,z=15}, enterpos = {x=1303,y=1664,z=15}, leavepos = {x=1301,y=1664,z=15}},
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if doors[item.actionid] then
		if player:getPosition() == Position(doors[item.actionid].enterpos) then
			player:teleportTo(Position(doors[item.actionid].leavepos), true)
		elseif not areaHasPlayer(Position(doors[item.actionid].centerpos), 3, 3) and not areaHasPlayer(Position(doors[item.actionid].enterpos), 1, 1) then
			player:teleportTo(Position(doors[item.actionid].enterpos), true)
		end
	end
	return true
end
