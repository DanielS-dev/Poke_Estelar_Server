// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_SIGNALHANDLINGTHREAD_H_01C6BF08B0EFE9E200175D108CF0B35F
#define FS_SIGNALHANDLINGTHREAD_H_01C6BF08B0EFE9E200175D108CF0B35F

#include <boost/asio.hpp>

class Signals
{
	boost::asio::signal_set set;
	public:
		explicit Signals(boost::asio::io_context& service);

	private:
		void asyncWait();
		static void dispatchSignalHandler(int signal);

		static void sigbreakHandler();
		static void sigintHandler();
		static void sighupHandler();
		static void sigtermHandler();
		static void sigusr1Handler();
};

#endif
