#pragma once

#include <Windows.h>
#include <string>
#include <fstream>
#include <commdlg.h>

class FileDialogue {
public:
	FileDialogue() = default;
	~FileDialogue() = default;

	static std::string OpenFile(const char* filterPattern = "Tilemap Files (*.map) | *.map\0*.map\0", HWND windowHandle = NULL);

	static std::string SaveFile(const char* filterPath = "Tilemap Files (*.map) | *.map\0*.map\0", HWND windowHandle = NULL);



};

