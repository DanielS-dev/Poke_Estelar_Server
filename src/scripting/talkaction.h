// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_TALKACTION_H_E6AABAC0F89843469526ADF310F3131C
#define FS_TALKACTION_H_E6AABAC0F89843469526ADF310F3131C

#include "luascript.h"
#include "baseevents.h"
#include "../core/const.h"

enum TalkActionResult_t {
	TALKACTION_CONTINUE,
	TALKACTION_BREAK,
	TALKACTION_FAILED,
};

class TalkAction;

class TalkActions : public BaseEvents
{
	public:
		TalkActions();
		~TalkActions();

		// non-copyable
		TalkActions(const TalkActions&) = delete;
		TalkActions& operator=(const TalkActions&) = delete;

		TalkActionResult_t playerSaySpell(Player* player, SpeakClasses type, const std::string& words) const;

	protected:
		LuaScriptInterface& getScriptInterface() final;
		std::string getScriptBaseName() const final;
		Event* getEvent(const std::string& nodeName) final;
		bool registerEvent(Event* event, const pugi::xml_node& node) final;
		void clear() final;

		// TODO: Store TalkAction objects directly in the list instead of using pointers
		std::forward_list<TalkAction*> talkActions;

		LuaScriptInterface scriptInterface;
};

class TalkAction : public Event
{
	public:
		explicit TalkAction(LuaScriptInterface* interface) : Event(interface) {}

		bool configureEvent(const pugi::xml_node& node) override;

		const std::string& getWords() const {
			return words;
		}
		char getSeparator() const {
			return separator;
		}

		//scripting
		bool executeSay(Player* player, const std::string& param, SpeakClasses type) const;
		//

	protected:
		std::string getScriptEventName() const override;

		std::string words;
		char separator = '"';
};

#endif
