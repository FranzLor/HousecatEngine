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


}

void ProjectManagement::SaveProject(const std::string& fileName, const std::vector<std::string>& assetID, const std::vector<std::string>& assetFilePath,
	const int& canvasWidth, const int& canvasHeight, const int& tileSize) {


}