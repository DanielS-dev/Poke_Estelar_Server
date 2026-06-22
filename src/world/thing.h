// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_THING_H_6F16A8E566AF4ACEAE02CF32A7246144
#define FS_THING_H_6F16A8E566AF4ACEAE02CF32A7246144

#include "../core/position.h"

class Tile;
class Cylinder;
class Item;
class Creature;
class Container;

class Thing
{
	protected:
		constexpr Thing() = default;
		~Thing() = default;

	public:
		// non-copyable
		Thing(const Thing&) = delete;
		Thing& operator=(const Thing&) = delete;

		virtual std::string getDescription(int32_t lookDistance) const = 0;

		virtual Cylinder* getParent() const {
			return nullptr;
		}
		virtual Cylinder* getRealParent() const {
			return getParent();
		}

		virtual void setParent(Cylinder*) {
			//
		}

		virtual Tile* getTile();
		virtual const Tile* getTile() const;

		virtual const Position& getPosition() const;
		virtual int32_t getThrowRange() const = 0;
		virtual bool isPushable() const = 0;

		virtual Container* getContainer() {
			return nullptr;
		}
		virtual const Container* getContainer() const {
			return nullptr;
		}
		virtual Item* getItem() {
			return nullptr;
		}
		virtual const Item* getItem() const {
			return nullptr;
		}
		virtual Creature* getCreature() {
			return nullptr;
		}
		virtual const Creature* getCreature() const {
			return nullptr;
		}

		virtual bool isRemoved() const {
			return true;
		}
};

#endif
