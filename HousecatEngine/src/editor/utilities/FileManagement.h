#pragma once

#include <Windows.h>
#include <string>

class FileManagement {
public:
	FileManagement() = default;
	~FileManagement() = default;

	static std::string OpenFile(const std::string& path);

	static std::string SaveFile(const std::string& path, const std::string& content);



};

