#include <fstream>
#include <filesystem>
#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>

#include "ProjectManagement.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"

#include "../../components/TransformComponent.h"
#include "../../components/SpriteComponent.h"

ProjectManagement::ProjectManagement() {}
ProjectManagement::~ProjectManagement() {}

void ProjectManagement::OpenProject(const std::string& fileName, EditorRenderer& renderer, std::shared_ptr<EditorCanvas>& canvas,
	const AssetManagerPtr& assetManager, std::vector<std::string>& assetID, std::vector<std::string>& assetFilePath,
	int& tileSize) {

	std::filesystem::path filePath = fileName;
	//map check
	if (filePath.extension() != ".map") {
		return;
	}

	//TODO map
	mapManagement->LoadMap(assetManager, fileName);

}

void ProjectManagement::SaveProject(const std::string& fileName, const std::vector<std::string>& assetID, const std::vector<std::string>& assetFilePath,
	const int& canvasWidth, const int& canvasHeight, const int& tileSize) {

	std::fstream projectFile;
	projectFile.open(fileName, std::ios::out | std::ios::trunc);

	if (!projectFile.is_open()) {
		//TODO
		//err handle
		return;
	}

	//map
	std::filesystem::path filePath(fileName);
	filePath.replace_extension(".map");

	//TODO
	//make method
	//write

	projectFile.close();

	std::fstream mapFile;
	mapFile.open(filePath, std::ios::out);

	if (!mapFile.is_open()) {
		//TODO
		//err handling
		return;
	}

	mapManagement->SaveMap(filePath);

}