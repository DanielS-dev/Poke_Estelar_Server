// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.h"

#include "protocolold.h"
#include "outputmessage.h"

#include "../game/game.h"

extern Game g_game;

void ProtocolOld::disconnectClient(const std::string& message)
{
	auto output = OutputMessagePool::getOutputMessage();
	output->addByte(0x0A);
	output->addString(message);
	send(output);

	disconnect();
}

void ProtocolOld::onRecvFirstMessage(NetworkMessage& msg)
{
	if (g_game.getGameState() == GAME_STATE_SHUTDOWN) {
		disconnect();
		return;
	}

	/*uint16_t clientOS =*/ msg.get<uint16_t>();
	uint16_t version = msg.get<uint16_t>();
	msg.skipBytes(12);

	if (version <= 760) {
		std::ostringstream ss;
		ss << "Only clients with protocol " << CLIENT_VERSION_STR << " allowed!";
		disconnectClient(ss.str());
		return;
	}

	if (!Protocol::RSA_decrypt(msg)) {
		disconnect();
		return;
	}

	uint32_t key[4];
	key[0] = msg.get<uint32_t>();
	key[1] = msg.get<uint32_t>();
	key[2] = msg.get<uint32_t>();
	key[3] = msg.get<uint32_t>();
	enableXTEAEncryption();
	setXTEAKey(key);

	if (version <= 822) {
		disableChecksum();
	}

	std::ostringstream ss;
	ss << "Only clients with protocol " << CLIENT_VERSION_STR << " allowed!";
	disconnectClient(ss.str());
}
