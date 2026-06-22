// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_DATABASETASKS_H_9CBA08E9F5FEBA7275CCEE6560059576
#define FS_DATABASETASKS_H_9CBA08E9F5FEBA7275CCEE6560059576

#include <condition_variable>
#include "../core/thread_holder_base.hpp"
#include "database.hpp"
#include "../core/enums.hpp"

struct DatabaseTask {
	DatabaseTask(std::string query, std::function<void(DBResult_ptr, bool)> callback, bool store) :
		query(std::move(query)), callback(std::move(callback)), store(store) {}

	std::string query;
	std::function<void(DBResult_ptr, bool)> callback;
	bool store;
};

class DatabaseTasks : public ThreadHolder<DatabaseTasks>
{
	public:
		DatabaseTasks() = default;
		void start();
		void flush();
		void shutdown();

		void addTask(const std::string& query, const std::function<void(DBResult_ptr, bool)>& callback = nullptr, bool store = false);

		void threadMain();
	private:
		void runTask(const DatabaseTask& task);

		Database db;
		std::thread thread;
		std::list<DatabaseTask> tasks;
		std::mutex taskLock;
		std::condition_variable taskSignal;
};

extern DatabaseTasks g_databaseTasks;

#endif
