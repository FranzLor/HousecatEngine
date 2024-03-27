#pragma once

#include <Windows.h>
#include <string>
#include <fstream>
#include <commdlg.h>

class FileDialogue {
public:
	FileDialogue() = default;
	~FileDialogue() = default;

	static std::string OpenFile(const char* filterPattern = "Lua Files (*.lua) |*.lua\0*.lua\0 Tilemap Files (*.map) | *.map\0*.map\0", HWND windowHandle = NULL);

	static std::string OpenTextureFile(const char* filterPattern = "Texture Files (*.png) | *.png\0*.png\0 JPEG Files (*.jpg) |*.jpg\0*.jpg\0", HWND windowHandle = NULL);

	static std::string SaveFile(const char* filterPath = "Lua Files (*.lua) |*.lua\0*.lua\0 Tilemap Files (*.map) | *.map\0*.map\0", HWND windowHandle = NULL);



};

