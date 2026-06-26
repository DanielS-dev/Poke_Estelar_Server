// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_LOGGER_H_63D82F8C77B449E5B5DFA71E879C41D0
#define FS_LOGGER_H_63D82F8C77B449E5B5DFA71E879C41D0

#include <condition_variable>
#include <cstdint>
#include <deque>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>

enum class LogLevel : uint8_t {
	Trace = 0,
	Debug,
	Info,
	Warn,
	Error,
	Fatal,
	Off
};

class Logger
{
	public:
		struct Config {
			LogLevel level = LogLevel::Info;
			bool console = true;
			bool file = true;
			std::string fileName = "logs/server.log";
			uint32_t maxFileSizeMb = 10;
			uint32_t maxFiles = 5;
		};

		static Logger& getInstance();

		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		void initialize(const Config& config);
		void initializeFromEnv(const std::string& fileName);
		void shutdown();

		bool shouldLog(LogLevel level) const;
		void log(LogLevel level, const std::string& category, const std::string& message, const char* file, int line);

	private:
		struct LogMessage {
			LogLevel level;
			std::string category;
			std::string message;
			std::string sourceFile;
			int line;
			std::string timestamp;
		};

		Logger() = default;
		~Logger();

		void threadMain();
		void writeMessage(const LogMessage& message);
		void rotateFileIfNeeded();

		Config config;
		std::ofstream fileStream;
		std::deque<LogMessage> queue;
		std::thread worker;
		mutable std::mutex mutex;
		std::condition_variable signal;
		bool running = false;
		bool initialized = false;
};

#define LOG_TRACE(category, message) Logger::getInstance().log(LogLevel::Trace, category, message, __FILE__, __LINE__)
#define LOG_DEBUG(category, message) Logger::getInstance().log(LogLevel::Debug, category, message, __FILE__, __LINE__)
#define LOG_INFO(category, message) Logger::getInstance().log(LogLevel::Info, category, message, __FILE__, __LINE__)
#define LOG_WARN(category, message) Logger::getInstance().log(LogLevel::Warn, category, message, __FILE__, __LINE__)
#define LOG_ERROR(category, message) Logger::getInstance().log(LogLevel::Error, category, message, __FILE__, __LINE__)
#define LOG_FATAL(category, message) Logger::getInstance().log(LogLevel::Fatal, category, message, __FILE__, __LINE__)

#endif
