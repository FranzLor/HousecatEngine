#pragma once

#include <Windows.h>
#include <string>
#include <fstream>
#include <commdlg.h>

class FileManagement {
public:
	FileManagement() = default;
	~FileManagement() = default;

	static std::string OpenFile(const char* filterPattern, HWND windowHandle);

	static std::string SaveFile(const char* filterPath, HWND windowHandle);



};

