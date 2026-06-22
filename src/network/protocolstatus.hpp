// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_STATUS_H_8B28B354D65B4C0483E37AD1CA316EB4
#define FS_STATUS_H_8B28B354D65B4C0483E37AD1CA316EB4

#include "networkmessage.hpp"
#include "protocol.hpp"

class ProtocolStatus final : public Protocol
{
	public:
		// static protocol information
		enum {server_sends_first = false};
		enum {protocol_identifier = 0xFF};
		enum {use_checksum = false};
		static const char* protocol_name() {
			return "status protocol";
		}

		explicit ProtocolStatus(Connection_ptr connection) : Protocol(connection) {}

		void onRecvFirstMessage(NetworkMessage& msg) final;

		void sendStatusString();
		void sendInfo(uint16_t requestedInfo, const std::string& characterName);

		static const uint64_t start;

	protected:
		static std::map<uint32_t, int64_t> ipConnectMap;
};

#endif
