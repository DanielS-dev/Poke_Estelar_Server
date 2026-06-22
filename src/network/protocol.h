// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_PROTOCOL_H_D71405071ACF4137A4B1203899DE80E1
#define FS_PROTOCOL_H_D71405071ACF4137A4B1203899DE80E1

#include "connection.h"

class Protocol : public std::enable_shared_from_this<Protocol>
{
	public:
		explicit Protocol(Connection_ptr connection) : connection(connection) {}
		virtual ~Protocol() = default;

		// non-copyable
		Protocol(const Protocol&) = delete;
		Protocol& operator=(const Protocol&) = delete;

		virtual void parsePacket(NetworkMessage&) {}

		virtual void onSendMessage(const OutputMessage_ptr& msg) const;
		void onRecvMessage(NetworkMessage& msg);
		virtual void onRecvFirstMessage(NetworkMessage& msg) = 0;
		virtual void onConnect() {}

		bool isConnectionExpired() const {
			return connection.expired();
		}

		Connection_ptr getConnection() const {
			return connection.lock();
		}

		uint32_t getIP() const;

		//Use this function for autosend messages only
		OutputMessage_ptr getOutputBuffer(int32_t size);

		OutputMessage_ptr& getCurrentBuffer() {
			return outputBuffer;
		}

		void send(OutputMessage_ptr msg) const {
			if (auto connection = getConnection()) {
				connection->send(msg);
			}
		}

	protected:
		void disconnect() const {
			if (auto connection = getConnection()) {
				connection->close();
			}
		}
		void enableXTEAEncryption() {
			encryptionEnabled = true;
		}
		void setXTEAKey(const uint32_t* key) {
			memcpy(this->key, key, sizeof(*key) * 4);
		}
		void disableChecksum() {
			checksumEnabled = false;
		}

		void XTEA_encrypt(OutputMessage& msg) const;
		bool XTEA_decrypt(NetworkMessage& msg) const;
		static bool RSA_decrypt(NetworkMessage& msg);

		void setRawMessages(bool value) {
			rawMessages = value;
		}

		virtual void release() {}
		friend class Connection;

		OutputMessage_ptr outputBuffer;
	private:
		const ConnectionWeak_ptr connection;
		uint32_t key[4] = {};
		bool encryptionEnabled = false;
		bool checksumEnabled = true;
		bool rawMessages = false;
};

#endif
