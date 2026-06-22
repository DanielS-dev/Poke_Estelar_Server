// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_OUTFIT_H_C56E7A707E3F422C8C93D9BE09916AA3
#define FS_OUTFIT_H_C56E7A707E3F422C8C93D9BE09916AA3

#include "../core/enums.hpp"

struct Outfit {
	Outfit(std::string name, uint16_t lookType, bool premium, bool unlocked) :
		name(std::move(name)), lookType(lookType), premium(premium), unlocked(unlocked) {}

	std::string name;
	uint16_t lookType;
	bool premium;
	bool unlocked;
};

struct ProtocolOutfit {
	ProtocolOutfit(const std::string& name, uint16_t lookType, uint8_t addons) :
		name(name), lookType(lookType), addons(addons) {}

	const std::string& name;
	uint16_t lookType;
	uint8_t addons;
};

class Outfits
{
	public:
		static Outfits* getInstance() {
			static Outfits instance;
			return &instance;
		}

		bool loadFromXml();

		const Outfit* getOutfitByLookType(PlayerSex_t sex, uint16_t lookType) const;
		const std::vector<Outfit>& getOutfits(PlayerSex_t sex) const {
			return outfits[sex];
		}

	private:
		std::vector<Outfit> outfits[PLAYERSEX_LAST + 1];
};

#endif
