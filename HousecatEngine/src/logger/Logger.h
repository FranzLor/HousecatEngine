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



enum LogType {
	LOG_LIFECYCLE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};

//individual log messages with their type and message content.
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




/*
*
* GENERAL EXAMPLES:
* Logger::Log("Entity Created: " + entity.GetID()");
* 
* Outputs to console with entity ID.
* 
* Logger::Error("Error Loading Texture: " + std::string(SDL_GetError()));
* 
* Outputs to console with SDL error message.
* 
*/

