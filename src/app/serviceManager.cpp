// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.h"

#include "server.h"

ServiceManager::~ServiceManager()
{
	stop();
}

void ServiceManager::die()
{
	io_service.stop();
}

void ServiceManager::run()
{
	assert(!running);
	running = true;
	io_service.run();
}

void ServiceManager::stop()
{
	if (!running) {
		return;
	}

	running = false;

	for (auto& servicePortIt : acceptors) {
		try {
			boost::asio::post(io_service, std::bind(&ServicePort::onStopServer, servicePortIt.second));
		} catch (boost::system::system_error& e) {
			std::cout << "[ServiceManager::stop] Network Error: " << e.what() << std::endl;
		}
	}

	acceptors.clear();

	death_timer.expires_after(std::chrono::seconds(3));
	death_timer.async_wait(std::bind(&ServiceManager::die, this));
}
