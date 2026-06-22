// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_PROTOCOLOLD_H_5487B862FE144AE0904D098A3238E161
#define FS_PROTOCOLOLD_H_5487B862FE144AE0904D098A3238E161

#include "protocol.h"

class NetworkMessage;

class ProtocolOld final : public Protocol
{
	public:
		// static protocol information
		enum {server_sends_first = false};
		enum {protocol_identifier = 0x01};
		enum {use_checksum = false};
		static const char* protocol_name() {
			return "old login protocol";
		}

		explicit ProtocolOld(Connection_ptr connection) : Protocol(connection) {}

		void onRecvFirstMessage(NetworkMessage& msg) final;

	protected:
		void disconnectClient(const std::string& message);
};

#endif
