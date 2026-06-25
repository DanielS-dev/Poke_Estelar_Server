// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

// Included inside LuaScriptInterface class declaration by ../luascript.hpp.

		// Party
		static int luaPartyDisband(lua_State* L);

		static int luaPartyGetLeader(lua_State* L);
		static int luaPartySetLeader(lua_State* L);

		static int luaPartyGetMembers(lua_State* L);
		static int luaPartyGetMemberCount(lua_State* L);

		static int luaPartyGetInvitees(lua_State* L);
		static int luaPartyGetInviteeCount(lua_State* L);

		static int luaPartyAddInvite(lua_State* L);
		static int luaPartyRemoveInvite(lua_State* L);

		static int luaPartyAddMember(lua_State* L);
		static int luaPartyRemoveMember(lua_State* L);

		static int luaPartyIsSharedExperienceActive(lua_State* L);
		static int luaPartyIsSharedExperienceEnabled(lua_State* L);
		static int luaPartyShareExperience(lua_State* L);
		static int luaPartySetSharedExperience(lua_State* L);
