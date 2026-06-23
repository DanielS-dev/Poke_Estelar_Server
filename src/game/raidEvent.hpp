// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_RAID_EVENT_H_3583C7C054584881856D55765DEDAFA9
#define FS_RAID_EVENT_H_3583C7C054584881856D55765DEDAFA9

#include <cstdint>
#include <list>
#include <string>
#include <utility>

#include "../core/const.hpp"
#include "../core/position.hpp"
#include "../scripting/baseevents.hpp"

struct MonsterSpawn {
	MonsterSpawn(std::string name, uint32_t minAmount, uint32_t maxAmount) :
		name(std::move(name)), minAmount(minAmount), maxAmount(maxAmount) {}

	std::string name;
	uint32_t minAmount;
	uint32_t maxAmount;
};

static constexpr int32_t MAXIMUM_TRIES_PER_MONSTER = 10;
static constexpr int32_t RAID_MINTICKS = 1000;

class RaidEvent
{
	public:
		virtual ~RaidEvent() = default;

		virtual bool configureRaidEvent(const pugi::xml_node& eventNode);

		virtual bool executeEvent() = 0;
		uint32_t getDelay() const {
			return delay;
		}

		static bool compareEvents(const RaidEvent* lhs, const RaidEvent* rhs) {
			return lhs->getDelay() < rhs->getDelay();
		}

	private:
		uint32_t delay;
};

class AnnounceEvent final : public RaidEvent
{
	public:
		AnnounceEvent() = default;

		bool configureRaidEvent(const pugi::xml_node& eventNode) final;

		bool executeEvent() final;

	private:
		std::string message;
		MessageClasses messageType = MESSAGE_EVENT_ADVANCE;
};

class SingleSpawnEvent final : public RaidEvent
{
	public:
		bool configureRaidEvent(const pugi::xml_node& eventNode) final;

		bool executeEvent() final;

	private:
		std::string monsterName;
		Position position;
};

class AreaSpawnEvent final : public RaidEvent
{
	public:
		bool configureRaidEvent(const pugi::xml_node& eventNode) final;

		bool executeEvent() final;

	private:
		std::list<MonsterSpawn> spawnList;
		Position fromPos, toPos;
};

class ScriptEvent final : public RaidEvent, public Event
{
	public:
		explicit ScriptEvent(LuaScriptInterface* interface) : Event(interface) {}

		bool configureRaidEvent(const pugi::xml_node& eventNode) final;
		bool configureEvent(const pugi::xml_node&) final {
			return false;
		}

		bool executeEvent() final;

	protected:
		std::string getScriptEventName() const final;
};

#endif
