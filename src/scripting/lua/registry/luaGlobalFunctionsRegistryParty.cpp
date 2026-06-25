// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../luascript.hpp"

void LuaScriptInterface::registerPartyBindings()
{
	// Party
	registerClass("Party", "", nullptr);
	registerMetaMethod("Party", "__eq", LuaScriptInterface::luaUserdataCompare);

	registerMethod("Party", "disband", LuaScriptInterface::luaPartyDisband);

	registerMethod("Party", "getLeader", LuaScriptInterface::luaPartyGetLeader);
	registerMethod("Party", "setLeader", LuaScriptInterface::luaPartySetLeader);

	registerMethod("Party", "getMembers", LuaScriptInterface::luaPartyGetMembers);
	registerMethod("Party", "getMemberCount", LuaScriptInterface::luaPartyGetMemberCount);

	registerMethod("Party", "getInvitees", LuaScriptInterface::luaPartyGetInvitees);
	registerMethod("Party", "getInviteeCount", LuaScriptInterface::luaPartyGetInviteeCount);

	registerMethod("Party", "addInvite", LuaScriptInterface::luaPartyAddInvite);
	registerMethod("Party", "removeInvite", LuaScriptInterface::luaPartyRemoveInvite);

	registerMethod("Party", "addMember", LuaScriptInterface::luaPartyAddMember);
	registerMethod("Party", "removeMember", LuaScriptInterface::luaPartyRemoveMember);

	registerMethod("Party", "isSharedExperienceActive", LuaScriptInterface::luaPartyIsSharedExperienceActive);
	registerMethod("Party", "isSharedExperienceEnabled", LuaScriptInterface::luaPartyIsSharedExperienceEnabled);
	registerMethod("Party", "shareExperience", LuaScriptInterface::luaPartyShareExperience);
	registerMethod("Party", "setSharedExperience", LuaScriptInterface::luaPartySetSharedExperience);
}
