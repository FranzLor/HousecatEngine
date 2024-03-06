//VS disables localtime warning
#pragma warning(disable:4996) 

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include "Logger.h" 


std::vector<LogMessage> Logger::messages;

static const char* COLOR_RESET = "\033[0m";
static const char* LIGHT_BLUE = "\033[94m";
static const char* GREEN = "\x1B[32m";
static const char* YELLOW = "\033[93m";
static const char* RED = "\033[31m";
static const char* MAGENTA = "\033[35m";

std::string CurrentDateTime() {
	std::time_t current = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');
	std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&current));
	
	return output;
}

void Logger::Lifecycle(const std::string& message) {
	LogMessage logMessage;

	logMessage.type = LOG_DEBUG;
	logMessage.message = "LIFECYLE: [" + CurrentDateTime() + "] - " + message;

	std::cout << LIGHT_BLUE << logMessage.message << COLOR_RESET << std::endl;

	messages.push_back(logMessage);
}



void Logger::Debug(const std::string& message) {
	LogMessage logMessage;

	logMessage.type = LOG_DEBUG;
	logMessage.message = "DEBUG: [" + CurrentDateTime() + "] - " + message;

	std::cout << MAGENTA << logMessage.message << COLOR_RESET << std::endl;

	messages.push_back(logMessage);
}


void Logger::Log(const std::string& message) {
	LogMessage logMessage;

	logMessage.type = LOG_INFO;
	logMessage.message = "LOG: [" + CurrentDateTime() + "] - " + message;

	std::cout << GREEN << logMessage.message << COLOR_RESET << std::endl;

	messages.push_back(logMessage);
}


void Logger::Warning(const std::string& message) {
	LogMessage logMessage;

	logMessage.type = LOG_WARNING;
	logMessage.message = "WARNING: [" + CurrentDateTime() + "] - " + message;

	std::cout << YELLOW << logMessage.message << COLOR_RESET << std::endl;

	messages.push_back(logMessage);
}


void Logger::Error(const std::string& message) {
	LogMessage logMessage;

	logMessage.type = LOG_ERROR;
	logMessage.message = "ERROR: [" + CurrentDateTime() + "] - " + message;
	std::cout << RED << logMessage.message << COLOR_RESET << std::endl;

	messages.push_back(logMessage);
}