// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.h"

#include "tasks.h"
#include "../game/game.h"

extern Game g_game;

void Dispatcher::threadMain()
{
	// NOTE: second argument defer_lock is to prevent from immediate locking
	std::unique_lock<std::mutex> taskLockUnique(taskLock, std::defer_lock);

	while (getState() != THREAD_STATE_TERMINATED) {
		// check if there are tasks waiting
		taskLockUnique.lock();

		if (taskList.empty()) {
			//if the list is empty wait for signal
			taskSignal.wait(taskLockUnique);
		}

		if (!taskList.empty()) {
			// take the first task
			Task* task = taskList.front();
			taskList.pop_front();
			taskLockUnique.unlock();

			if (!task->hasExpired()) {
				++dispatcherCycle;
				// execute it
				(*task)();

				g_game.map.clearSpectatorCache();
			}
			delete task;
		} else {
			taskLockUnique.unlock();
		}
	}
}

void Dispatcher::addTask(Task* task, bool push_front /*= false*/)
{
	bool do_signal = false;

	taskLock.lock();

	if (getState() == THREAD_STATE_RUNNING) {
		do_signal = taskList.empty();

		if (push_front) {
			taskList.push_front(task);
		} else {
			taskList.push_back(task);
		}
	} else {
		delete task;
	}

	taskLock.unlock();

	// send a signal if the list was empty
	if (do_signal) {
		taskSignal.notify_one();
	}
}

void Dispatcher::shutdown()
{
	Task* task = createTask([this]() {
		setState(THREAD_STATE_TERMINATED);
		taskSignal.notify_one();
	});

	std::lock_guard<std::mutex> lockClass(taskLock);
	taskList.push_back(task);

	taskSignal.notify_one();
}
