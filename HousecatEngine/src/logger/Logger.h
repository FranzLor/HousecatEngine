#pragma once

#include <string>
#include <vector>

#include <SDL.h>
#include <imgui/imgui.h>


//----------------------------------------------------//
//                    LOGGER CLASS                    //
//     Handles logging across different log levels    //
//   and outputs to console with timestamped entries. //
//----------------------------------------------------//

/**
 * @enum LogType
 * @brief Defines the category of log messages.
 *
 * - LOG_LIFECYCLE: Logs related to object lifecycle (creation, destruction).
 * - LOG_DEBUG: Logs intended for debugging purposes.
 * - LOG_INFO: Informational logs that provide insights into the application's operation.
 * - LOG_WARNING: Warnings about potential issues that are not immediately critical.
 * - LOG_ERROR: Critical error messages that could halt or severely affect operations.
 */

enum LogType {
	LOG_LIFECYCLE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};

/**
 * @struct LogMessage
 * @brief Represents a single log message with a type and text content.
 *
 * This struct encapsulates the data necessary to record a log entry, which includes
 * the log type and the actual message string.
 */

struct LogMessage {
	LogType type;
	std::string message;
};

class Logger {
public:
	static std::vector<LogMessage> messages;

	//used for constructors / destructors
	static void Lifecycle(const std::string& message);

	//used to track | debug
	static void Debug(const std::string& message);

	//used for general logging
	static void Log(const std::string& message);

	//not critical but require attention
	static void Warning(const std::string& message);

	//critical errors
	static void Error(const std::string& message);

	//outputs version of SDL being used
	static void SDLVersion();

	//outputs the version of ImGui being used
	static void ImGuiVersion();

	Logger() {}
	~Logger() {}

};




/**
 *
 * @class Logger
 * @brief Provides static methods for logging different types of messages
 *        with automatic timestamping and type categorization.
 *
 * Logger supports logging messages at various levels, from debug to critical errors,
 * with an interface for adding SDL and ImGui version logging. It centralizes the logging
 * mechanism to standardize how messages are displayed and stored. This class is intended
 * to be used across the system for consistent logging practices.
 *
 * Usage:
 *  Logger::Lifecycle("Game Contructor Called!");
 *  Logger::Debug("Player Position: " + playerPosition.ToString());
 *  Logger::Log("Key Pressed: " + key);
 *  Logger::Warning("Entity Table in Lua Script is Empty");
 *	Logger::Error(Failed to Load SDL Texture: " + SDL_GetError());
 *
 * The logger outputs to the console and can store logs for later retrieval or inspection.
 * 
 */