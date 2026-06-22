// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_PROTOCOLLOGIN_H_1238F4B473074DF2ABC595C29E81C46D
#define FS_PROTOCOLLOGIN_H_1238F4B473074DF2ABC595C29E81C46D

#include "protocol.h"

class NetworkMessage;
class OutputMessage;

class ProtocolLogin : public Protocol
{
	public:
		// static protocol information
		enum {server_sends_first = false};
		enum {protocol_identifier = 0x01};
		enum {use_checksum = true};
		static const char* protocol_name() {
			return "login protocol";
		}

		explicit ProtocolLogin(Connection_ptr connection) : Protocol(connection) {}

		void onRecvFirstMessage(NetworkMessage& msg);

	protected:
		void disconnectClient(const std::string& message, uint16_t version);

		void getCharacterList(const std::string& accountName, const std::string& password, const std::string& token, uint16_t version);
};

#endif
