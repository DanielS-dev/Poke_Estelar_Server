// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "../items.hpp"
#include "../../core/logger.hpp"
#include "../../core/tools/stringsTools.hpp"
#include "../../core/tools/systemTools.hpp"

FILELOADER_ERRORS Items::loadFromOtb(const std::string& file)
{
	FileLoader f;
	if (!f.openFile(file.c_str(), "OTBI")) {
		return f.getError();
	}

	uint32_t type;
	NODE node = f.getChildNode(NO_NODE, type);

	PropStream props;
	if (f.getProps(node, props)) {
		//4 byte flags
		//attributes
		//0x01 = version data
		uint32_t flags;
		if (!props.read<uint32_t>(flags)) {
			return ERROR_INVALID_FORMAT;
		}

		uint8_t attr;
		if (!props.read<uint8_t>(attr)) {
			return ERROR_INVALID_FORMAT;
		}

		if (attr == ROOT_ATTR_VERSION) {
			uint16_t datalen;
			if (!props.read<uint16_t>(datalen)) {
				return ERROR_INVALID_FORMAT;
			}

			if (datalen != sizeof(VERSIONINFO)) {
				return ERROR_INVALID_FORMAT;
			}

			VERSIONINFO vi;
			if (!props.read(vi)) {
				return ERROR_INVALID_FORMAT;
			}

			majorVersion = vi.dwMajorVersion; //items otb format file version
			minorVersion = vi.dwMinorVersion; //client version
			buildNumber = vi.dwBuildNumber; //revision
		}
	}

	if (majorVersion == 0xFFFFFFFF) {
		LOG_WARN("Items", "items.otb is using a generic client version.");
	} else if (majorVersion != 3) {
		LOG_ERROR("Items", "Old items.otb version detected. A newer version is required.");
		return ERROR_INVALID_FORMAT;
	} else if (minorVersion < CLIENT_VERSION_1098) {
		LOG_ERROR("Items", "items.otb client version is too old. A newer version is required.");
		return ERROR_INVALID_FORMAT;
	}

	node = f.getChildNode(node, type);
	while (node != NO_NODE) {
		PropStream stream;
		if (!f.getProps(node, stream)) {
			return f.getError();
		}

		uint32_t flags;
		if (!stream.read<uint32_t>(flags)) {
			return ERROR_INVALID_FORMAT;
		}

		uint16_t serverId = 0;
		uint16_t clientId = 0;
		uint16_t speed = 0;
		uint16_t wareId = 0;
		uint8_t lightLevel = 0;
		uint8_t lightColor = 0;
		uint8_t alwaysOnTopOrder = 0;

		uint8_t attrib;
		while (stream.read<uint8_t>(attrib)) {
			uint16_t datalen;
			if (!stream.read<uint16_t>(datalen)) {
				return ERROR_INVALID_FORMAT;
			}

			switch (attrib) {
				case ITEM_ATTR_SERVERID: {
					if (datalen != sizeof(uint16_t)) {
						return ERROR_INVALID_FORMAT;
					}

					if (!stream.read<uint16_t>(serverId)) {
						return ERROR_INVALID_FORMAT;
					}

					if (serverId > 30000 && serverId < 30100) {
						serverId -= 30000;
					}
					break;
				}

				case ITEM_ATTR_CLIENTID: {
					if (datalen != sizeof(uint16_t)) {
						return ERROR_INVALID_FORMAT;
					}

					if (!stream.read<uint16_t>(clientId)) {
						return ERROR_INVALID_FORMAT;
					}
					break;
				}

				case ITEM_ATTR_SPEED: {
					if (datalen != sizeof(uint16_t)) {
						return ERROR_INVALID_FORMAT;
					}

					if (!stream.read<uint16_t>(speed)) {
						return ERROR_INVALID_FORMAT;
					}
					break;
				}

				case ITEM_ATTR_LIGHT2: {
					if (datalen != sizeof(lightBlock2)) {
						return ERROR_INVALID_FORMAT;
					}

					lightBlock2 lb2;
					if (!stream.read(lb2)) {
						return ERROR_INVALID_FORMAT;
					}

					lightLevel = static_cast<uint8_t>(lb2.lightLevel);
					lightColor = static_cast<uint8_t>(lb2.lightColor);
					break;
				}

				case ITEM_ATTR_TOPORDER: {
					if (datalen != sizeof(uint8_t)) {
						return ERROR_INVALID_FORMAT;
					}

					if (!stream.read<uint8_t>(alwaysOnTopOrder)) {
						return ERROR_INVALID_FORMAT;
					}
					break;
				}

				case ITEM_ATTR_WAREID: {
					if (datalen != sizeof(uint16_t)) {
						return ERROR_INVALID_FORMAT;
					}

					if (!stream.read<uint16_t>(wareId)) {
						return ERROR_INVALID_FORMAT;
					}
					break;
				}

				default: {
					//skip unknown attributes
					if (!stream.skip(datalen)) {
						return ERROR_INVALID_FORMAT;
					}
					break;
				}
			}
		}

		reverseItemMap.emplace(clientId, serverId);

		// store the found item
		if (serverId >= items.size()) {
			items.resize(serverId + 1);
		}
		ItemType& iType = items[serverId];

		iType.group = static_cast<itemgroup_t>(type);
		switch (type) {
			case ITEM_GROUP_CONTAINER:
				iType.type = ITEM_TYPE_CONTAINER;
				break;
			case ITEM_GROUP_DOOR:
				//not used
				iType.type = ITEM_TYPE_DOOR;
				break;
			case ITEM_GROUP_MAGICFIELD:
				//not used
				iType.type = ITEM_TYPE_MAGICFIELD;
				break;
			case ITEM_GROUP_TELEPORT:
				//not used
				iType.type = ITEM_TYPE_TELEPORT;
				break;
			case ITEM_GROUP_NONE:
			case ITEM_GROUP_GROUND:
			case ITEM_GROUP_SPLASH:
			case ITEM_GROUP_FLUID:
			case ITEM_GROUP_CHARGES:
			case ITEM_GROUP_DEPRECATED:
				break;
			default:
				return ERROR_INVALID_FORMAT;
		}

		iType.blockSolid = hasBitSet(FLAG_BLOCK_SOLID, flags);
		iType.blockProjectile = hasBitSet(FLAG_BLOCK_PROJECTILE, flags);
		iType.blockPathFind = hasBitSet(FLAG_BLOCK_PATHFIND, flags);
		iType.hasHeight = hasBitSet(FLAG_HAS_HEIGHT, flags);
		iType.useable = hasBitSet(FLAG_USEABLE, flags);
		iType.pickupable = hasBitSet(FLAG_PICKUPABLE, flags);
		iType.moveable = hasBitSet(FLAG_MOVEABLE, flags);
		iType.stackable = hasBitSet(FLAG_STACKABLE, flags);

		iType.alwaysOnTop = hasBitSet(FLAG_ALWAYSONTOP, flags);
		iType.isVertical = hasBitSet(FLAG_VERTICAL, flags);
		iType.isHorizontal = hasBitSet(FLAG_HORIZONTAL, flags);
		iType.isHangable = hasBitSet(FLAG_HANGABLE, flags);
		iType.allowDistRead = hasBitSet(FLAG_ALLOWDISTREAD, flags);
		iType.rotatable = hasBitSet(FLAG_ROTATABLE, flags);
		iType.canReadText = hasBitSet(FLAG_READABLE, flags);
		iType.lookThrough = hasBitSet(FLAG_LOOKTHROUGH, flags);
		iType.isAnimation = hasBitSet(FLAG_ANIMATION, flags);
		// iType.walkStack = !hasBitSet(FLAG_FULLTILE, flags);
		iType.forceUse = hasBitSet(FLAG_FORCEUSE, flags);

		iType.id = serverId;
		iType.clientId = clientId;
		iType.speed = speed;
		iType.lightLevel = lightLevel;
		iType.lightColor = lightColor;
		iType.wareId = wareId;
		iType.alwaysOnTopOrder = alwaysOnTopOrder;

		node = f.getNextNode(node, type);
	}

	items.shrink_to_fit();
	LOG_INFO("Items", "Loaded " + std::to_string(items.size()) + " item entries from " + file);
	return ERROR_NONE;
}

