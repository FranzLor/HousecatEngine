#pragma once

#include <string>
#include <memory>
#include <filesystem>
#include <sol/sol.hpp>

#include "SDLUtility.h"
#include "LuaExporter.h"

#include "../ui/EditorCanvas.h"
#include "../../assetmanager/AssetManager.h"


//-----------------------------------------------------//
//                ProjectManagement                    //
//  Manages loading and saving of project files and    //
//  map data in the Housecat game engine. This class   //
//  facilitates the import and export of project       //
//  configurations and tile map data, handling both    //
//  .lua and .map file formats.                        //
//-----------------------------------------------------//


class ProjectManagement {
private:
	void LoadMap(const AssetManagerPtr& assetManager, const std::string& fileName);
	void SaveMap(std::filesystem::path fileName);

public:
	ProjectManagement();
	~ProjectManagement();
	
	void OpenProject(sol::state& lua, const std::string& fileName, EditorRenderer& renderer, std::shared_ptr<EditorCanvas>& canvas,
		const AssetManagerPtr& assetManager, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath,
		int& tileSize);
	 
	void SaveProject(const std::string& fileName, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath,
		const int& canvasWidth, const int& canvasHeight, const int& tileSize);

	void SaveAsLua(const std::string& fileName, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath, const int& tileSize);

};



/**
 * @file ProjectManagement.h
 * @brief Manages project file operations in the Housecat game engine.
 *
 * The ProjectManagement class is designed to manage project and map files within
 * the Housecat game engine. It supports operations such as opening and saving projects,
 * and loading and saving tile maps. The class uses Lua scripts for project files and
 * custom format for map files, providing comprehensive tools for managing game content.
 *
 * Key Features:
 * - Open and save project configurations in Lua format.
 * - Load and save tile maps.
 * - Integrate seamlessly with LuaExporter to handle export operations.
 * - Manage file paths and handle file operations with error checking.
 */

