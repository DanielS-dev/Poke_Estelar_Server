// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.h"

#include "databasetasks.h"
#include "../core/tasks.h"

extern Dispatcher g_dispatcher;


void DatabaseTasks::start()
{
	db.connect();
	ThreadHolder::start();
}

void DatabaseTasks::threadMain()
{
	std::unique_lock<std::mutex> taskLockUnique(taskLock, std::defer_lock);
	while (getState() != THREAD_STATE_TERMINATED) {
		taskLockUnique.lock();
		if (tasks.empty()) {
			taskSignal.wait(taskLockUnique);
		}

		if (!tasks.empty()) {
			DatabaseTask task = std::move(tasks.front());
			tasks.pop_front();
			taskLockUnique.unlock();
			runTask(task);
		} else {
			taskLockUnique.unlock();
		}
	}
}

void DatabaseTasks::addTask(const std::string& query, const std::function<void(DBResult_ptr, bool)>& callback/* = nullptr*/, bool store/* = false*/)
{
	bool signal = false;
	taskLock.lock();
	if (getState() == THREAD_STATE_RUNNING) {
		signal = tasks.empty();
		tasks.emplace_back(query, callback, store);
	}
	taskLock.unlock();

	if (signal) {
		taskSignal.notify_one();
	}
}

void DatabaseTasks::runTask(const DatabaseTask& task)
{
	bool success;
	DBResult_ptr result;
	if (task.store) {
		result = db.storeQuery(task.query);
		success = true;
	} else {
		result = nullptr;
		success = db.executeQuery(task.query);
	}

	if (task.callback) {
		g_dispatcher.addTask(createTask(std::bind(task.callback, result, success)));
	}
}

void DatabaseTasks::flush()
{
	while (!tasks.empty()) {
		runTask(tasks.front());
		tasks.pop_front();
	}
}

void DatabaseTasks::shutdown()
{
	taskLock.lock();
	setState(THREAD_STATE_TERMINATED);
	flush();
	taskLock.unlock();
	taskSignal.notify_one();
}
