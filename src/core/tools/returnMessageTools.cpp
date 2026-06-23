// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "returnMessageTools.hpp"

const char* getReturnMessage(ReturnValue value)
{
	switch (value) {
		case RETURNVALUE_DESTINATIONOUTOFREACH:
			return "Destination is out of reach.";
		case RETURNVALUE_NOTMOVEABLE:
			return "You cannot move this object.";
		case RETURNVALUE_DROPTWOHANDEDITEM:
			return "Drop the double-handed object first.";
		case RETURNVALUE_BOTHHANDSNEEDTOBEFREE:
			return "Both hands need to be free.";
		case RETURNVALUE_CANNOTBEDRESSED:
			return "You cannot dress this object there.";
		case RETURNVALUE_PUTTHISOBJECTINYOURHAND:
			return "Put this object in your hand.";
		case RETURNVALUE_PUTTHISOBJECTINBOTHHANDS:
			return "Put this object in both hands.";
		case RETURNVALUE_CANONLYUSEONEWEAPON:
			return "You may only use one weapon.";
		case RETURNVALUE_TOOFARAWAY:
			return "Too far away.";
		case RETURNVALUE_FIRSTGODOWNSTAIRS:
			return "First go downstairs.";
		case RETURNVALUE_FIRSTGOUPSTAIRS:
			return "First go upstairs.";
		case RETURNVALUE_NOTENOUGHCAPACITY:
			return "This object is too heavy for you to carry.";
		case RETURNVALUE_CONTAINERNOTENOUGHROOM:
			return "You cannot put more objects in this container.";
		case RETURNVALUE_NEEDEXCHANGE:
		case RETURNVALUE_NOTENOUGHROOM:
			return "There is not enough room.";
		case RETURNVALUE_CANNOTPICKUP:
			return "You cannot take this object.";
		case RETURNVALUE_CANNOTTHROW:
			return "You cannot throw there.";
		case RETURNVALUE_THEREISNOWAY:
			return "There is no way.";
		case RETURNVALUE_THISISIMPOSSIBLE:
			return "This is impossible.";
		case RETURNVALUE_PLAYERISPZLOCKED:
			return "You can not enter a protection zone after attacking another player.";
		case RETURNVALUE_PLAYERISNOTINVITED:
			return "You are not invited.";
		case RETURNVALUE_CREATUREDOESNOTEXIST:
			return "Creature does not exist.";
		case RETURNVALUE_DEPOTISFULL:
			return "You cannot put more items in this depot.";
		case RETURNVALUE_CANNOTUSETHISOBJECT:
			return "You cannot use this object.";
		case RETURNVALUE_PLAYERWITHTHISNAMEISNOTONLINE:
			return "A player with this name is not online.";
		case RETURNVALUE_NOTREQUIREDLEVELTOUSERUNE:
			return "You do not have the required magic level to use this rune.";
		case RETURNVALUE_YOUAREALREADYTRADING:
			return "You are already trading.";
		case RETURNVALUE_THISPLAYERISALREADYTRADING:
			return "This player is already trading.";
		case RETURNVALUE_YOUMAYNOTLOGOUTDURINGAFIGHT:
			return "You may not logout during or immediately after a fight!";
		case RETURNVALUE_DIRECTPLAYERSHOOT:
			return "You are not allowed to shoot directly on players.";
		case RETURNVALUE_NOTENOUGHLEVEL:
			return "You do not have enough level.";
		case RETURNVALUE_NOTENOUGHMAGICLEVEL:
			return "You do not have enough magic level.";
		case RETURNVALUE_NOTENOUGHMANA:
			return "You do not have enough mana.";
		case RETURNVALUE_NOTENOUGHSOUL:
			return "You do not have enough soul.";
		case RETURNVALUE_YOUAREEXHAUSTED:
			return "You are exhausted.";
		case RETURNVALUE_CANONLYUSETHISRUNEONCREATURES:
			return "You can only use this rune on creatures.";
		case RETURNVALUE_PLAYERISNOTREACHABLE:
			return "Player is not reachable.";
		case RETURNVALUE_CREATUREISNOTREACHABLE:
			return "Creature is not reachable.";
		case RETURNVALUE_ACTIONNOTPERMITTEDINPROTECTIONZONE:
			return "This action is not permitted in a protection zone.";
		case RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER:
			return "You may not attack this player.";
		case RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE:
			return "You may not attack this creature.";
		case RETURNVALUE_YOUMAYNOTATTACKAPERSONINPROTECTIONZONE:
			return "You may not attack a person in a protection zone.";
		case RETURNVALUE_YOUMAYNOTATTACKAPERSONWHILEINPROTECTIONZONE:
			return "You may not attack a person while you are in a protection zone.";
		case RETURNVALUE_YOUCANONLYUSEITONCREATURES:
			return "You can only use it on creatures.";
		case RETURNVALUE_TURNSECUREMODETOATTACKUNMARKEDPLAYERS:
			return "Turn secure mode off if you really want to attack unmarked players.";
		case RETURNVALUE_YOUNEEDPREMIUMACCOUNT:
			return "You need a premium account.";
		case RETURNVALUE_YOUNEEDTOLEARNTHISSPELL:
			return "You need to learn this spell first.";
		case RETURNVALUE_YOURVOCATIONCANNOTUSETHISSPELL:
			return "Your vocation cannot use this spell.";
		case RETURNVALUE_YOUNEEDAWEAPONTOUSETHISSPELL:
			return "You need to equip a weapon to use this spell.";
		case RETURNVALUE_PLAYERISPZLOCKEDLEAVEPVPZONE:
			return "You can not leave a pvp zone after attacking another player.";
		case RETURNVALUE_PLAYERISPZLOCKEDENTERPVPZONE:
			return "You can not enter a pvp zone after attacking another player.";
		case RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE:
			return "This action is not permitted in a non pvp zone.";
		case RETURNVALUE_YOUCANNOTLOGOUTHERE:
			return "You can not logout here.";
		case RETURNVALUE_YOUNEEDAMAGICITEMTOCASTSPELL:
			return "You need a magic item to cast this spell.";
		case RETURNVALUE_CANNOTCONJUREITEMHERE:
			return "You cannot conjure items here.";
		case RETURNVALUE_YOUNEEDTOSPLITYOURSPEARS:
			return "You need to split your spears first.";
		case RETURNVALUE_NAMEISTOOAMBIGIOUS:
			return "Name is too ambigious.";
		case RETURNVALUE_CANONLYUSEONESHIELD:
			return "You may use only one shield.";
		case RETURNVALUE_NOPARTYMEMBERSINRANGE:
			return "No party members in range.";
		case RETURNVALUE_YOUARENOTTHEOWNER:
			return "You are not the owner.";
		default:
			return "Sorry, not possible.";
	}
}
