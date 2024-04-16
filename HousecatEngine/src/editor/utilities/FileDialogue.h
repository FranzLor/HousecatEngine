#pragma once

#include <Windows.h>
#include <string>
#include <fstream>
#include <commdlg.h>


//-----------------------------------------------------//
//                    FileDialogue                     //
//   Utilizes Windows' Common Dialog Box Libraries to  //
//    provide file selection dialogs for opening and   //
//    saving files. Designed specifically for Windows. //
//-----------------------------------------------------//


class FileDialogue {
public:
	FileDialogue() = default;
	~FileDialogue() = default;

	static std::string OpenFile(const char* filterPattern = "Lua Files (*.lua) |*.lua\0*.lua\0 Tilemap Files (*.map) | *.map\0*.map\0", HWND windowHandle = NULL);

	static std::string OpenTextureFile(const char* filterPattern = "Texture Files (*.png) | *.png\0*.png\0 JPEG Files (*.jpg) |*.jpg\0*.jpg\0", HWND windowHandle = NULL);

	static std::string SaveFile(const char* filterPath = "Lua Files (*.lua) |*.lua\0*.lua\0 Tilemap Files (*.map) | *.map\0*.map\0", HWND windowHandle = NULL);

};




/**
 * @file FileDialogue.h
 * @brief Handles file dialog interactions on Windows systems.
 *
 * The FileDialogue class provides static methods to open and save files using
 * Windows common dialog boxes. It simplifies file selection for opening and
 * saving various file types such as Lua scripts, texture images, and tilemap files.
 * It is designed specifically for use on Windows platforms and utilizes the
 * Windows API to present standard file dialog interfaces to the user.
 *
 * Features:
 * - Open files with customizable filter patterns.
 * - Save files with pre-defined extensions.
 * - Handle both general and texture-specific file types.
 *
 * Usage:
 * - Call `OpenFile` to open general files with a specified filter.
 * - Call `OpenTextureFile` for image files like PNGs and JPGs.
 * - Call `SaveFile` to save files with a specified filter.
 *
 * Note:
 * - This class is Windows-specific and uses Windows API functions.
 */