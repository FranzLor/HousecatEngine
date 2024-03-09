#include <vector>

#include "FileDialogue.h"

std::string FileDialogue::OpenFile(const char* filterPattern, HWND windowHandle) {
	//dynamic allo for longer paths
	std::vector<char> selectedFilePath(MAX_PATH);
	//zero init the struct
	OPENFILENAMEA openFileDialogStruct = { 0 };

	ZeroMemory(&openFileDialogStruct, sizeof(openFileDialogStruct));

	openFileDialogStruct.lStructSize = sizeof(openFileDialogStruct);
	openFileDialogStruct.hwndOwner = windowHandle;
	openFileDialogStruct.lpstrFilter = filterPattern;
	//ptr to buffer's first element
	openFileDialogStruct.lpstrFile = selectedFilePath.data();
	openFileDialogStruct.nMaxFile = selectedFilePath.size();
	openFileDialogStruct.Flags = OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	openFileDialogStruct.nFilterIndex = 1;

	if (GetOpenFileNameA(&openFileDialogStruct)) {
		//string from vector to ensure null-terminated
		return std::string(selectedFilePath.begin(), std::find(selectedFilePath.begin(), selectedFilePath.end(), '\0'));
	}

	return std::string();
}

std::string FileDialogue::SaveFile(const char* filterPath, HWND windowHandle) {
	std::vector<char> filePath(MAX_PATH);
	OPENFILENAMEA saveFileDialogStruct = { 0 };

	saveFileDialogStruct.lStructSize = sizeof(saveFileDialogStruct);
	saveFileDialogStruct.hwndOwner = windowHandle;
	saveFileDialogStruct.lpstrFilter = filterPath;
	saveFileDialogStruct.lpstrFile = filePath.data();
	saveFileDialogStruct.nMaxFile = filePath.size();
	saveFileDialogStruct.Flags = OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	saveFileDialogStruct.nFilterIndex = 1;

	if (GetSaveFileNameA(&saveFileDialogStruct)) {
		return std::string(filePath.begin(), std::find(filePath.begin(), filePath.end(), '\0'));
	}

	return std::string();
}