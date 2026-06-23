// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "chatLoader.hpp"
#include "chat.hpp"
#include "../../core/pugicast.hpp"
#include "../../core/tools/xmlErro.hpp"

bool ChatLoader::load(Chat& chat)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/chatchannels/chatchannels.xml");
	if (!result) {
		printXMLError("Error - Chat::load", "data/chatchannels/chatchannels.xml", result);
		return false;
	}

	std::forward_list<uint16_t> removedChannels;
	for (auto& channelEntry : chat.normalChannels) {
		ChatChannel& channel = channelEntry.second;
		channel.onSpeakEvent = -1;
		channel.canJoinEvent = -1;
		channel.onJoinEvent = -1;
		channel.onLeaveEvent = -1;
		removedChannels.push_front(channelEntry.first);
	}

	for (auto channelNode : doc.child("channels").children()) {
		ChatChannel channel(pugi::cast<uint16_t>(channelNode.attribute("id").value()), channelNode.attribute("name").as_string());
		channel.publicChannel = channelNode.attribute("public").as_bool();

		pugi::xml_attribute scriptAttribute = channelNode.attribute("script");
		if (scriptAttribute) {
			if (chat.scriptInterface.loadFile("data/chatchannels/scripts/" + std::string(scriptAttribute.as_string())) == 0) {
				channel.onSpeakEvent = chat.scriptInterface.getEvent("onSpeak");
				channel.canJoinEvent = chat.scriptInterface.getEvent("canJoin");
				channel.onJoinEvent = chat.scriptInterface.getEvent("onJoin");
				channel.onLeaveEvent = chat.scriptInterface.getEvent("onLeave");
			} else {
				std::cout << "[Warning - Chat::load] Can not load script: " << scriptAttribute.as_string() << std::endl;
			}
		}

		removedChannels.remove(channel.id);
		chat.normalChannels[channel.id] = channel;
	}

	for (uint16_t channelId : removedChannels) {
		chat.normalChannels.erase(channelId);
	}
	return true;
}
