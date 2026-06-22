// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.h"

#include "outputmessage.h"
#include "protocol.h"
#include "../core/lockfree.h"
#include "../core/scheduler.h"

extern Scheduler g_scheduler;

const uint16_t OUTPUTMESSAGE_FREE_LIST_CAPACITY = 2048;
const std::chrono::milliseconds OUTPUTMESSAGE_AUTOSEND_DELAY {10};

class OutputMessageAllocator
{
	public:
		typedef OutputMessage value_type;
		template<typename U>
		struct rebind {typedef LockfreePoolingAllocator<U, OUTPUTMESSAGE_FREE_LIST_CAPACITY> other;};
};

void OutputMessagePool::scheduleSendAll()
{
	auto functor = std::bind(&OutputMessagePool::sendAll, this);
	g_scheduler.addEvent(createSchedulerTask(OUTPUTMESSAGE_AUTOSEND_DELAY.count(), functor));
}

void OutputMessagePool::sendAll()
{
	//dispatcher thread
	for (auto& protocol : bufferedProtocols) {
		auto& msg = protocol->getCurrentBuffer();
		if (msg) {
			protocol->send(std::move(msg));
		}
	}

	if (!bufferedProtocols.empty()) {
		scheduleSendAll();
	}
}

void OutputMessagePool::addProtocolToAutosend(Protocol_ptr protocol)
{
	//dispatcher thread
	if (bufferedProtocols.empty()) {
		scheduleSendAll();
	}
	bufferedProtocols.emplace_back(protocol);
}

void OutputMessagePool::removeProtocolFromAutosend(const Protocol_ptr& protocol)
{
	//dispatcher thread
	auto it = std::find(bufferedProtocols.begin(), bufferedProtocols.end(), protocol);
	if (it != bufferedProtocols.end()) {
		std::swap(*it, bufferedProtocols.back());
		bufferedProtocols.pop_back();
	}
}

OutputMessage_ptr OutputMessagePool::getOutputMessage()
{
	return std::allocate_shared<OutputMessage>(OutputMessageAllocator());
}
