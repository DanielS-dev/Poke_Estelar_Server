// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include <bitset>

#include "../player.hpp"
#include "../../world/bed.hpp"
#include "../../game/chat/chat.hpp"
#include "../../game/combat/combat.hpp"
#include "../../config/configmanager.hpp"
#include "../../scripting/creatureevent/creatureevent.hpp"
#include "../../scripting/events/events.hpp"
#include "../../game/game.hpp"
#include "../../persistence/login/iologindata.hpp"
#include "../monster.hpp"
#include "../../game/movement/movement.hpp"
#include "../../core/scheduler.hpp"
#include "../../game/weapons/weapons.hpp"
#include "../../core/tools/gameEnumTools.hpp"
#include "../../core/tools/random.hpp"
#include "../../core/tools/returnMessageTools.hpp"
#include "../../core/tools/stringsTools.hpp"

extern ConfigManager g_config;
extern Game g_game;
extern Chat* g_chat;
extern Vocations g_vocations;
extern MoveEvents* g_moveEvents;
extern Weapons* g_weapons;
extern CreatureEvents* g_creatureEvents;
extern Events* g_events;

void Player::notifyStatusChange(Player* loginPlayer, VipStatus_t status)
{
	if (!client) {
		return;
	}

	auto it = VIPList.find(loginPlayer->guid);
	if (it == VIPList.end()) {
		return;
	}

	client->sendUpdatedVIPStatus(loginPlayer->guid, status);

	if (status == VIPSTATUS_ONLINE) {
		client->sendTextMessage(TextMessage(MESSAGE_STATUS_SMALL, loginPlayer->getName() + " has logged in."));
	} else if (status == VIPSTATUS_OFFLINE) {
		client->sendTextMessage(TextMessage(MESSAGE_STATUS_SMALL, loginPlayer->getName() + " has logged out."));
	}
}


bool Player::removeVIP(uint32_t vipGuid)
{
	if (VIPList.erase(vipGuid) == 0) {
		return false;
	}

	IOLoginData::removeVIPEntry(accountNumber, vipGuid);
	return true;
}


bool Player::addVIP(uint32_t vipGuid, const std::string& vipName, VipStatus_t status)
{
	if (guid == vipGuid) {
		sendTextMessage(MESSAGE_STATUS_SMALL, "You cannot add yourself.");
		return false;
	}

	if (VIPList.size() >= getMaxVIPEntries() || VIPList.size() == 200) { // max number of buddies is 200 in 9.53
		sendTextMessage(MESSAGE_STATUS_SMALL, "You cannot add more buddies.");
		return false;
	}

	auto result = VIPList.insert(vipGuid);
	if (!result.second) {
		sendTextMessage(MESSAGE_STATUS_SMALL, "This player is already in your list.");
		return false;
	}

	IOLoginData::addVIPEntry(accountNumber, vipGuid, "", 0, false);
	if (client) {
		client->sendVIP(vipGuid, vipName, "", 0, false, status);
	}
	return true;
}


bool Player::addVIPInternal(uint32_t vipGuid)
{
	if (guid == vipGuid) {
		return false;
	}

	if (VIPList.size() >= getMaxVIPEntries() || VIPList.size() == 200) { // max number of buddies is 200 in 9.53
		return false;
	}

	return VIPList.insert(vipGuid).second;
}


bool Player::editVIP(uint32_t vipGuid, const std::string& description, uint32_t icon, bool notify)
{
	auto it = VIPList.find(vipGuid);
	if (it == VIPList.end()) {
		return false; // player is not in VIP
	}

	IOLoginData::editVIPEntry(accountNumber, vipGuid, description, icon, notify);
	return true;
}

//close container and its child containers

void Player::setSex(PlayerSex_t newSex)
{
	sex = newSex;
}


Skulls_t Player::getSkull() const
{
	if (hasFlag(PlayerFlag_NotGainInFight)) {
		return SKULL_NONE;
	}
	return skull;
}


Skulls_t Player::getSkullClient(const Creature* creature) const
{
	// if (!creature || g_game.getWorldType() != WORLD_TYPE_PVP) {
		// return SKULL_NONE;
	// }

	const Player* player = creature->getPlayer();
	if (player && player->getSkull() == SKULL_NONE) {
		if (isInWar(player)) {
			return SKULL_GREEN;
		}

		if (!player->getGuildWarList().empty() && guild == player->getGuild()) {
			return SKULL_GREEN;
		}

		if (player->hasAttacked(this)) {
			return SKULL_YELLOW;
		}

		if (isPartner(player)) {
			return SKULL_GREEN;
		}
	}
	return Creature::getSkullClient(creature);
}


bool Player::hasAttacked(const Player* attacked) const
{
	if (hasFlag(PlayerFlag_NotGainInFight) || !attacked) {
		return false;
	}

	return attackedSet.find(attacked->guid) != attackedSet.end();
}


void Player::addAttacked(const Player* attacked)
{
	if (hasFlag(PlayerFlag_NotGainInFight) || !attacked || attacked == this) {
		return;
	}

	attackedSet.insert(attacked->guid);
}


void Player::clearAttacked()
{
	attackedSet.clear();
}


void Player::addUnjustifiedDead(const Player* attacked)
{
	if (hasFlag(PlayerFlag_NotGainInFight) || attacked == this || g_game.getWorldType() == WORLD_TYPE_PVP_ENFORCED) {
		return;
	}

	sendTextMessage(MESSAGE_EVENT_ADVANCE, "Warning! The murder of " + attacked->getName() + " was not justified.");

	skullTicks += g_config.getNumber(ConfigManager::FRAG_TIME);

	if (getSkull() != SKULL_BLACK) {
		if (g_config.getNumber(ConfigManager::KILLS_TO_BLACK) != 0 && skullTicks > (g_config.getNumber(ConfigManager::KILLS_TO_BLACK) - 1) * static_cast<int64_t>(g_config.getNumber(ConfigManager::FRAG_TIME))) {
			setSkull(SKULL_BLACK);
		} else if (getSkull() != SKULL_RED && g_config.getNumber(ConfigManager::KILLS_TO_RED) != 0 && skullTicks > (g_config.getNumber(ConfigManager::KILLS_TO_RED) - 1) * static_cast<int64_t>(g_config.getNumber(ConfigManager::FRAG_TIME))) {
			setSkull(SKULL_RED);
		}
	}
}


void Player::checkSkullTicks(int32_t ticks)
{
	int32_t newTicks = skullTicks - ticks;
	if (newTicks < 0) {
		skullTicks = 0;
	} else {
		skullTicks = newTicks;
	}

	if ((skull == SKULL_RED || skull == SKULL_BLACK) && skullTicks < 1000 && !hasCondition(CONDITION_INFIGHT)) {
		setSkull(SKULL_NONE);
	}
}


bool Player::isPromoted() const
{
	uint16_t promotedVocation = g_vocations.getPromotedVocation(vocation->getId());
	return promotedVocation == VOCATION_NONE && vocation->getId() != promotedVocation;
}


double Player::getLostPercent() const
{
	int32_t blessingCount = std::bitset<5>(blessings).count();

	int32_t deathLosePercent = g_config.getNumber(ConfigManager::DEATH_LOSE_PERCENT);
	if (deathLosePercent != -1) {
		if (isPromoted()) {
			deathLosePercent -= 3;
		}

		deathLosePercent -= blessingCount;
		return std::max<int32_t>(0, deathLosePercent) / 100.;
	}

	double lossPercent;
	if (level >= 25) {
		double tmpLevel = level + (levelPercent / 100.);
		lossPercent = static_cast<double>((tmpLevel + 50) * 50 * ((tmpLevel * tmpLevel) - (5 * tmpLevel) + 8)) / experience;
	} else {
		lossPercent = 10;
	}

	if (isPromoted()) {
		lossPercent *= 0.7;
	}
	if (blessingCount > 0) {
		return 0;
	}

	return lossPercent * pow(0.92, blessingCount) / 100;
}


void Player::learnInstantSpell(const std::string& spellName)
{
	if (!hasLearnedInstantSpell(spellName)) {
		learnedInstantSpellList.push_front(spellName);
	}
}


void Player::forgetInstantSpell(const std::string& spellName)
{
	learnedInstantSpellList.remove(spellName);
}


bool Player::hasLearnedInstantSpell(const std::string& spellName) const
{
	if (hasFlag(PlayerFlag_CannotUseSpells)) {
		return false;
	}

	if (hasFlag(PlayerFlag_IgnoreSpellCheck)) {
		return true;
	}

	for (const auto& learnedSpellName : learnedInstantSpellList) {
		if (strcasecmp(learnedSpellName.c_str(), spellName.c_str()) == 0) {
			return true;
		}
	}
	return false;
}


bool Player::isInWar(const Player* player) const
{
	if (!player || !guild) {
		return false;
	}

	const Guild* playerGuild = player->getGuild();
	if (!playerGuild) {
		return false;
	}

	return isInWarList(playerGuild->getId()) && player->isInWarList(guild->getId());
}


bool Player::isInWarList(uint32_t guildId) const
{
	return std::find(guildWarList.begin(), guildWarList.end(), guildId) != guildWarList.end();
}


bool Player::isPremium() const
{
	if (g_config.getBoolean(ConfigManager::FREE_PREMIUM) || hasFlag(PlayerFlag_IsAlwaysPremium)) {
		return true;
	}

	return premiumDays > 0;
}


void Player::setPremiumDays(int32_t v)
{
	premiumDays = v;
	sendBasicData();
}


PartyShields_t Player::getPartyShield(const Player* player) const
{
	if (!player) {
		return SHIELD_NONE;
	}

	if (party) {
		if (party->getLeader() == player) {
			if (party->isSharedExperienceActive()) {
				if (party->isSharedExperienceEnabled()) {
					return SHIELD_YELLOW_SHAREDEXP;
				}

				if (party->canUseSharedExperience(player)) {
					return SHIELD_YELLOW_NOSHAREDEXP;
				}

				return SHIELD_YELLOW_NOSHAREDEXP_BLINK;
			}

			return SHIELD_YELLOW;
		}

		if (player->party == party) {
			if (party->isSharedExperienceActive()) {
				if (party->isSharedExperienceEnabled()) {
					return SHIELD_BLUE_SHAREDEXP;
				}

				if (party->canUseSharedExperience(player)) {
					return SHIELD_BLUE_NOSHAREDEXP;
				}

				return SHIELD_BLUE_NOSHAREDEXP_BLINK;
			}

			return SHIELD_BLUE;
		}

		if (isInviting(player)) {
			return SHIELD_WHITEBLUE;
		}
	}

	if (player->isInviting(this)) {
		return SHIELD_WHITEYELLOW;
	}

	if (player->party) {
		return SHIELD_GRAY;
	}

	return SHIELD_NONE;
}


bool Player::isInviting(const Player* player) const
{
	if (!player || !party || party->getLeader() != this) {
		return false;
	}
	return party->isPlayerInvited(player);
}


bool Player::isPartner(const Player* player) const
{
	if (!player || !party) {
		return false;
	}
	return party == player->party;
}


bool Player::isGuildMate(const Player* player) const
{
	if (!player || !guild) {
		return false;
	}
	return guild == player->guild;
}


void Player::sendPlayerPartyIcons(Player* player)
{
	sendCreatureShield(player);
	sendCreatureSkull(player);
}


bool Player::addPartyInvitation(Party* party)
{
	auto it = std::find(invitePartyList.begin(), invitePartyList.end(), party);
	if (it != invitePartyList.end()) {
		return false;
	}

	invitePartyList.push_front(party);
	return true;
}


void Player::removePartyInvitation(Party* party)
{
	invitePartyList.remove(party);
}


void Player::clearPartyInvitations()
{
	for (Party* invitingParty : invitePartyList) {
		invitingParty->removeInvite(*this, false);
	}
	invitePartyList.clear();
}


GuildEmblems_t Player::getGuildEmblem(const Player* player) const
{
	if (!player) {
		return GUILDEMBLEM_NONE;
	}

	const Guild* playerGuild = player->getGuild();
	if (!playerGuild) {
		return GUILDEMBLEM_NONE;
	}

	if (player->getGuildWarList().empty()) {
		if (guild == playerGuild) {
			return GUILDEMBLEM_MEMBER;
		} else {
			return GUILDEMBLEM_OTHER;
		}
	} else if (guild == playerGuild) {
		return GUILDEMBLEM_ALLY;
	} else if (isInWar(player)) {
		return GUILDEMBLEM_ENEMY;
	}

	return GUILDEMBLEM_NEUTRAL;
}

uint8_t Player::getCurrentMount() const
{
	int32_t value;
	if (getStorageValue(PSTRG_MOUNTS_CURRENTMOUNT, value)) {
		return value;
	}
	return 0;
}


void Player::setCurrentMount(uint8_t mount)
{
	addStorageValue(PSTRG_MOUNTS_CURRENTMOUNT, mount);
}


bool Player::toggleMount(bool mount)
{
	if ((OTSYS_TIME() - lastToggleMount) < 3000 && !wasMounted) {
		sendCancelMessage(RETURNVALUE_YOUAREEXHAUSTED);
		return false;
	}

	if (mount) {
		if (isMounted()) {
			return false;
		}

		if (!group->access && tile->hasFlag(TILESTATE_PROTECTIONZONE)) {
			sendCancelMessage(RETURNVALUE_ACTIONNOTPERMITTEDINPROTECTIONZONE);
			return false;
		}

		const Outfit* playerOutfit = Outfits::getInstance()->getOutfitByLookType(getSex(), defaultOutfit.lookType);
		if (!playerOutfit) {
			return false;
		}

		uint8_t currentMountId = getCurrentMount();
		if (currentMountId == 0) {
			sendOutfitWindow();
			return false;
		}

		Mount* currentMount = g_game.mounts.getMountByID(currentMountId);
		if (!currentMount) {
			return false;
		}

		if (!hasMount(currentMount)) {
			setCurrentMount(0);
			sendOutfitWindow();
			return false;
		}

		if (currentMount->premium && !isPremium()) {
			sendCancelMessage(RETURNVALUE_YOUNEEDPREMIUMACCOUNT);
			return false;
		}

		if (hasCondition(CONDITION_OUTFIT)) {
			sendCancelMessage(RETURNVALUE_NOTPOSSIBLE);
			return false;
		}

		defaultOutfit.lookMount = currentMount->clientId;

		if (currentMount->speed != 0) {
			g_game.changeSpeed(this, currentMount->speed);
		}
	} else {
		if (!isMounted()) {
			return false;
		}

		dismount();
	}

	g_game.internalCreatureChangeOutfit(this, defaultOutfit);
	lastToggleMount = OTSYS_TIME();
	return true;
}


bool Player::tameMount(uint8_t mountId)
{
	if (!g_game.mounts.getMountByID(mountId)) {
		return false;
	}

	const uint8_t tmpMountId = mountId - 1;
	const uint32_t key = PSTRG_MOUNTS_RANGE_START + (tmpMountId / 31);

	int32_t value;
	if (getStorageValue(key, value)) {
		value |= (1 << (tmpMountId % 31));
	} else {
		value = (1 << (tmpMountId % 31));
	}

	addStorageValue(key, value);
	return true;
}


bool Player::untameMount(uint8_t mountId)
{
	if (!g_game.mounts.getMountByID(mountId)) {
		return false;
	}

	const uint8_t tmpMountId = mountId - 1;
	const uint32_t key = PSTRG_MOUNTS_RANGE_START + (tmpMountId / 31);

	int32_t value;
	if (!getStorageValue(key, value)) {
		return true;
	}

	value &= ~(1 << (tmpMountId % 31));
	addStorageValue(key, value);

	if (getCurrentMount() == mountId) {
		if (isMounted()) {
			dismount();
			g_game.internalCreatureChangeOutfit(this, defaultOutfit);
		}

		setCurrentMount(0);
	}

	return true;
}


bool Player::hasMount(const Mount* mount) const
{
	if (isAccessPlayer()) {
		return true;
	}

	if (mount->premium && !isPremium()) {
		return false;
	}

	const uint8_t tmpMountId = mount->id - 1;

	int32_t value;
	if (!getStorageValue(PSTRG_MOUNTS_RANGE_START + (tmpMountId / 31), value)) {
		return false;
	}

	return ((1 << (tmpMountId % 31)) & value) != 0;
}


void Player::dismount()
{
	Mount* mount = g_game.mounts.getMountByID(getCurrentMount());
	if (mount && mount->speed > 0) {
		g_game.changeSpeed(this, -mount->speed);
	}

	defaultOutfit.lookMount = 0;
}


size_t Player::getMaxVIPEntries() const
{
	if (group->maxVipEntries != 0) {
		return group->maxVipEntries;
	} else if (isPremium()) {
		return 100;
	}
	return 20;
}


size_t Player::getMaxDepotItems() const
{
	if (group->maxDepotItems != 0) {
		return group->maxDepotItems;
	} else if (isPremium()) {
		return 2000;
	}
	return 1000;
}


void Player::setGuild(Guild* guild)
{
	if (guild == this->guild) {
		return;
	}

	Guild* oldGuild = this->guild;

	this->guildNick.clear();
	this->guild = nullptr;
	this->guildRank = nullptr;

	if (guild) {
		const GuildRank* rank = guild->getRankByLevel(1);
		if (!rank) {
			return;
		}

		this->guild = guild;
		this->guildRank = rank;
		guild->addMember(this);
	}

	if (oldGuild) {
		oldGuild->removeMember(this);
	}
}

