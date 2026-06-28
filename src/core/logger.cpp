// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "otpch.hpp"

#include "logger.hpp"

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cerrno>
#include <ctime>
#include <cstring>
#include <sys/stat.h>
#include <utility>

#ifdef _WIN32
#include <direct.h>
#endif

namespace {
	const char* getLevelName(LogLevel level)
	{
		switch (level) {
			case LogLevel::Trace: return "trace";
			case LogLevel::Debug: return "debug";
			case LogLevel::Info: return "info";
			case LogLevel::Warn: return "warn";
			case LogLevel::Error: return "error";
			case LogLevel::Fatal: return "fatal";
			default: return "off";
		}
	}

	std::string trim(const std::string& value)
	{
		auto start = std::find_if_not(value.begin(), value.end(), [](unsigned char ch) {
			return std::isspace(ch) != 0;
		});

		auto end = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char ch) {
			return std::isspace(ch) != 0;
		}).base();

		if (start >= end) {
			return std::string();
		}
		return std::string(start, end);
	}

	std::string asLower(std::string value)
	{
		std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
			return static_cast<char>(std::tolower(ch));
		});
		return value;
	}

	std::string parseEnvValue(std::string value)
	{
		value = trim(value);
		if (value.empty()) {
			return value;
		}

		const char quote = value.front();
		if (quote == '"' || quote == '\'') {
			const size_t endQuote = value.find(quote, 1);
			if (endQuote != std::string::npos) {
				return value.substr(1, endQuote - 1);
			}
			return value.substr(1);
		}

		const size_t comment = value.find('#');
		if (comment != std::string::npos) {
			value.erase(comment);
		}
		return trim(value);
	}

	std::map<std::string, std::string> loadEnvFile(const std::string& fileName)
	{
		std::map<std::string, std::string> env;
		std::ifstream file(fileName);
		if (!file.is_open()) {
			return env;
		}

		std::string line;
		while (std::getline(file, line)) {
			line = trim(line);
			if (line.empty() || line.front() == '#') {
				continue;
			}

			const size_t separator = line.find('=');
			if (separator == std::string::npos) {
				continue;
			}

			const std::string key = trim(line.substr(0, separator));
			if (!key.empty()) {
				env[key] = parseEnvValue(line.substr(separator + 1));
			}
		}
		return env;
	}

	bool getEnvBoolean(const std::map<std::string, std::string>& env, const char* key, bool defaultValue)
	{
		auto it = env.find(key);
		if (it == env.end()) {
			return defaultValue;
		}

		const std::string value = asLower(trim(it->second));
		return value == "1" || value == "true" || value == "yes" || value == "on";
	}

	uint32_t getEnvNumber(const std::map<std::string, std::string>& env, const char* key, uint32_t defaultValue)
	{
		auto it = env.find(key);
		if (it == env.end()) {
			return defaultValue;
		}

		char* end = nullptr;
		const unsigned long value = std::strtoul(it->second.c_str(), &end, 10);
		if (end == it->second.c_str() || *end != '\0') {
			return defaultValue;
		}
		return static_cast<uint32_t>(value);
	}

	std::string getEnvString(const std::map<std::string, std::string>& env, const char* key, const char* defaultValue)
	{
		auto it = env.find(key);
		if (it == env.end()) {
			return defaultValue;
		}
		return it->second;
	}

	LogLevel parseLevel(const std::string& value)
	{
		const std::string level = asLower(trim(value));
		if (level == "trace") {
			return LogLevel::Trace;
		}
		if (level == "debug") {
			return LogLevel::Debug;
		}
		if (level == "warn" || level == "warning") {
			return LogLevel::Warn;
		}
		if (level == "error") {
			return LogLevel::Error;
		}
		if (level == "fatal") {
			return LogLevel::Fatal;
		}
		if (level == "off") {
			return LogLevel::Off;
		}
		return LogLevel::Info;
	}

	std::string getTimestamp()
	{
		const auto now = std::chrono::system_clock::now();
		const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
		const std::time_t time = std::chrono::system_clock::to_time_t(now);

		std::tm localTime;
#ifdef _WIN32
		localtime_s(&localTime, &time);
#else
		localtime_r(&time, &localTime);
#endif

		char buffer[32];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);

		std::ostringstream stream;
		stream << buffer << '.' << std::setw(3) << std::setfill('0') << millis.count();
		return stream.str();
	}

	std::string getParentDirectory(const std::string& fileName)
	{
		const size_t slash = fileName.find_last_of("/\\");
		if (slash == std::string::npos) {
			return std::string();
		}
		return fileName.substr(0, slash);
	}

	std::string joinPath(const std::string& directory, const std::string& fileName)
	{
		if (directory.empty()) {
			return fileName;
		}

		const char last = directory.back();
		if (last == '/' || last == '\\') {
			return directory + fileName;
		}
		return directory + '/' + fileName;
	}

	void createDirectory(const std::string& path)
	{
		if (path.empty()) {
			return;
		}

#ifdef _WIN32
		_mkdir(path.c_str());
#else
		mkdir(path.c_str(), 0755);
#endif
	}

	void createDirectories(const std::string& path)
	{
		std::string current;
		for (char ch : path) {
			current.push_back(ch);
			if (ch == '/' || ch == '\\') {
				createDirectory(current);
			}
		}
		createDirectory(current);
	}

	uint64_t getFileSize(const std::string& fileName)
	{
		std::ifstream file(fileName, std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			return 0;
		}
		return static_cast<uint64_t>(file.tellg());
	}
}

Logger& Logger::getInstance()
{
	static Logger logger;
	return logger;
}

Logger::~Logger()
{
	shutdown();
}

void Logger::initialize(const Config& loggerConfig)
{
	shutdown();

	{
		std::lock_guard<std::mutex> lock(mutex);
		config = loggerConfig;

		if (config.file) {
			if (config.splitFilesByLevel) {
				createDirectories(config.directory);
			} else {
				createDirectories(getParentDirectory(config.fileName));
				openFileStream(fileStream, config.fileName);
			}
		}

		running = true;
		initialized = true;
	}

	worker = std::thread(&Logger::threadMain, this);
}

void Logger::initializeFromEnv(const std::string& fileName)
{
	const auto env = loadEnvFile(fileName);

	Config loggerConfig;
	const std::string globalLevel = getEnvString(env, "LOG_LEVEL", "info");
	loggerConfig.level = parseLevel(globalLevel);
	loggerConfig.consoleLevel = parseLevel(getEnvString(env, "LOG_CONSOLE_LEVEL", globalLevel.c_str()));
	loggerConfig.fileLevel = parseLevel(getEnvString(env, "LOG_FILE_LEVEL", globalLevel.c_str()));
	loggerConfig.console = getEnvBoolean(env, "LOG_TO_CONSOLE", true);
	loggerConfig.file = getEnvBoolean(env, "LOG_TO_FILE", true);
	loggerConfig.splitFilesByLevel = getEnvBoolean(env, "LOG_SPLIT_BY_LEVEL", true);
	loggerConfig.fileName = getEnvString(env, "LOG_FILE", "logs/server.log");
	loggerConfig.directory = getEnvString(env, "LOG_DIR", "logs");
	loggerConfig.maxFileSizeMb = getEnvNumber(env, "LOG_MAX_FILE_SIZE_MB", 10);
	loggerConfig.maxFiles = getEnvNumber(env, "LOG_MAX_FILES", 5);

	initialize(loggerConfig);
}

void Logger::shutdown()
{
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (!initialized) {
			return;
		}
		running = false;
	}

	signal.notify_all();

	if (worker.joinable()) {
		worker.join();
	}

	std::lock_guard<std::mutex> lock(mutex);
	if (fileStream.is_open()) {
		fileStream.flush();
		fileStream.close();
	}
	for (auto& it : levelFileStreams) {
		if (it.second.is_open()) {
			it.second.flush();
			it.second.close();
		}
	}
	levelFileStreams.clear();

	queue.clear();
	initialized = false;
}

bool Logger::shouldLog(LogLevel level) const
{
	std::lock_guard<std::mutex> lock(mutex);
	if (!initialized || config.level == LogLevel::Off) {
		return false;
	}

	if (level < config.level) {
		return false;
	}

	const bool shouldLogToConsole = config.console && config.consoleLevel != LogLevel::Off && level >= config.consoleLevel;
	const bool shouldLogToFile = config.file && config.fileLevel != LogLevel::Off && level >= config.fileLevel;
	return shouldLogToConsole || shouldLogToFile;
}

void Logger::log(LogLevel level, const std::string& category, const std::string& message, const char* file, int line)
{
	LogMessage logMessage;
	logMessage.level = level;
	logMessage.category = category;
	logMessage.message = message;
	logMessage.sourceFile = file ? file : "";
	logMessage.line = line;
	logMessage.timestamp = getTimestamp();

	{
		std::lock_guard<std::mutex> lock(mutex);
		if (!initialized || config.level == LogLevel::Off) {
			return;
		}

		if (level < config.level) {
			return;
		}

		const bool shouldLogToConsole = config.console && config.consoleLevel != LogLevel::Off && level >= config.consoleLevel;
		const bool shouldLogToFile = config.file && config.fileLevel != LogLevel::Off && level >= config.fileLevel;
		if (!shouldLogToConsole && !shouldLogToFile) {
			return;
		}

		queue.push_back(std::move(logMessage));
	}
	signal.notify_one();
}

void Logger::threadMain()
{
	while (true) {
		LogMessage message;

		{
			std::unique_lock<std::mutex> lock(mutex);
			signal.wait(lock, [this] {
				return !running || !queue.empty();
			});

			if (queue.empty()) {
				if (!running) {
					break;
				}
				continue;
			}

			message = std::move(queue.front());
			queue.pop_front();
		}

		writeMessage(message);
	}
}

void Logger::writeMessage(const LogMessage& message)
{
	std::ostringstream stream;
	stream << '[' << message.timestamp << "] [" << getLevelName(message.level) << "] [" << message.category << "] " << message.message;
	if (!message.sourceFile.empty()) {
		stream << " (" << message.sourceFile << ':' << message.line << ')';
	}

	if (config.console && config.consoleLevel != LogLevel::Off && message.level >= config.consoleLevel) {
		if (message.level == LogLevel::Info) {
			std::cout << '[' << message.category << "] " << message.message << std::endl;
		} else {
			std::cout << '[' << getLevelName(message.level) << "] [" << message.category << "] " << message.message << std::endl;
		}
	}

	if (config.file && config.fileLevel != LogLevel::Off && message.level >= config.fileLevel) {
		std::ofstream* output = getFileStream(message.level);
		if (output && output->is_open()) {
			const std::string fileName = getFileName(message.level);
			rotateFileIfNeeded(fileName, *output);
			*output << stream.str() << std::endl;
		}
	}
}

std::ofstream* Logger::getFileStream(LogLevel level)
{
	if (!config.file) {
		return nullptr;
	}

	if (!config.splitFilesByLevel) {
		if (!fileStream.is_open() && !openFileStream(fileStream, config.fileName)) {
			return nullptr;
		}
		return &fileStream;
	}

	auto it = levelFileStreams.find(level);
	if (it != levelFileStreams.end()) {
		return &it->second;
	}

	const std::string fileName = getFileName(level);
	createDirectories(getParentDirectory(fileName));

	auto result = levelFileStreams.emplace(level, std::ofstream());
	if (!openFileStream(result.first->second, fileName)) {
		return nullptr;
	}
	return &result.first->second;
}

std::string Logger::getFileName(LogLevel level) const
{
	if (!config.splitFilesByLevel) {
		return config.fileName;
	}

	std::ostringstream fileName;
	fileName << getLevelName(level) << ".log";
	return joinPath(config.directory, fileName.str());
}

void Logger::rotateFileIfNeeded(const std::string& fileName, std::ofstream& stream)
{
	if (config.maxFileSizeMb == 0 || config.maxFiles == 0) {
		return;
	}

	const uint64_t maxSize = static_cast<uint64_t>(config.maxFileSizeMb) * 1024 * 1024;
	if (getFileSize(fileName) < maxSize) {
		return;
	}

	if (stream.is_open()) {
		stream.close();
	}

	for (uint32_t i = config.maxFiles; i > 0; --i) {
		std::ostringstream current;
		current << fileName << '.' << i;

		if (i == config.maxFiles) {
			std::remove(current.str().c_str());
			continue;
		}

		std::ostringstream next;
		next << fileName << '.' << (i + 1);
		std::rename(current.str().c_str(), next.str().c_str());
	}

	std::rename(fileName.c_str(), (fileName + ".1").c_str());
	openFileStream(stream, fileName);
}

void Logger::disableFileLogging(const std::string& reason)
{
	config.file = false;

	for (auto& it : levelFileStreams) {
		if (it.second.is_open()) {
			it.second.close();
		}
	}

	if (fileStream.is_open()) {
		fileStream.close();
	}

	std::cerr << "[error] [Logger] File logging disabled: " << reason << std::endl;
}

bool Logger::openFileStream(std::ofstream& stream, const std::string& fileName)
{
	stream.open(fileName, std::ios::app);
	if (stream.is_open()) {
		return true;
	}

	const std::string errorMessage = std::strerror(errno);
	disableFileLogging("failed to open log file '" + fileName + "': " + errorMessage);
	return false;
}
