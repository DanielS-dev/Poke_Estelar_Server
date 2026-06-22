// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_OUTPUTMESSAGE_H_C06AAED85C7A43939F22D229297C0CC1
#define FS_OUTPUTMESSAGE_H_C06AAED85C7A43939F22D229297C0CC1

#include "networkmessage.hpp"
#include "connection.hpp"
#include "../core/tools.hpp"

class Protocol;

class OutputMessage : public NetworkMessage
{
	public:
		OutputMessage() = default;

		// non-copyable
		OutputMessage(const OutputMessage&) = delete;
		OutputMessage& operator=(const OutputMessage&) = delete;

		uint8_t* getOutputBuffer() {
			return buffer + outputBufferStart;
		}

		void writeMessageLength() {
			add_header(info.length);
		}

		void addCryptoHeader(bool addChecksum) {
			if (addChecksum) {
				add_header(adlerChecksum(buffer + outputBufferStart, info.length));
			}

			writeMessageLength();
		}

		inline void append(const NetworkMessage& msg) {
			auto msgLen = msg.getLength();
			memcpy(buffer + info.position, msg.getBuffer() + 8, msgLen);
			info.length += msgLen;
			info.position += msgLen;
		}

		inline void append(const OutputMessage_ptr& msg) {
			auto msgLen = msg->getLength();
			memcpy(buffer + info.position, msg->getBuffer() + 8, msgLen);
			info.length += msgLen;
			info.position += msgLen;
		}

	protected:
		template <typename T>
		inline void add_header(T add) {
			assert(outputBufferStart >= sizeof(T));
			outputBufferStart -= sizeof(T);
			memcpy(buffer + outputBufferStart, &add, sizeof(T));
			//added header size to the message size
			info.length += sizeof(T);
		}

		MsgSize_t outputBufferStart = INITIAL_BUFFER_POSITION;
};

class OutputMessagePool
{
	public:
		// non-copyable
		OutputMessagePool(const OutputMessagePool&) = delete;
		OutputMessagePool& operator=(const OutputMessagePool&) = delete;

		static OutputMessagePool& getInstance() {
			static OutputMessagePool instance;
			return instance;
		}

		void sendAll();
		void scheduleSendAll();

		static OutputMessage_ptr getOutputMessage();

		void addProtocolToAutosend(Protocol_ptr protocol);
		void removeProtocolFromAutosend(const Protocol_ptr& protocol);
	private:
		OutputMessagePool() = default;
		//NOTE: A vector is used here because this container is mostly read
		//and relatively rarely modified (only when a client connects/disconnects)
		std::vector<Protocol_ptr> bufferedProtocols;
};


#endif
