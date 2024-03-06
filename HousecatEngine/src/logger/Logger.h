#pragma once

#include <string>
#include <vector>

enum LogType {
	LOG_LIFECYCLE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};

struct LogMessage {
	LogType type;
	std::string message;
};

class Logger {
public:
	static std::vector<LogMessage> messages;

	//use for constructors / destructors
	static void Lifecycle(const std::string& message);

	//use to track | debug
	static void Debug(const std::string& message);

	static void Log(const std::string& message);
	static void Warning(const std::string& message);
	static void Error(const std::string& message);

	Logger() {}
	~Logger() {}

};

