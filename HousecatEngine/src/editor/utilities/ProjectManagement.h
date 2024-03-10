#pragma once

#include <string>
#include <memory>
#include <filesystem>
#include <sol/sol.hpp>

#include "SDLUtility.h"

#include "../ui/EditorCanvas.h"
#include "../../assetmanager/AssetManager.h"

class ProjectManagement {
private:

public:
	ProjectManagement();
	~ProjectManagement();
	
	void OpenProject(const std::string& fileName, EditorRenderer& renderer, std::shared_ptr<EditorCanvas>& canvas,
		const AssetManagerPtr& assetManager, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath,
		int& tileSize);
	 
	void SaveProject(const std::string& fileName, const std::vector<std::string>& assetID, const std::vector<std::string>& assetFilePath,
		const int& canvasWidth, const int& canvasHeight, const int& tileSize);


	//TODO
	//save as
};

