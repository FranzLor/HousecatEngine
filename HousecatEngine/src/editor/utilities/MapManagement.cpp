#include <SDL.h>
#include <fstream>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>

#include "MapManagement.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"

#include "../../components/TransformComponent.h"
#include "../../components/SpriteComponent.h"

void MapManagement::LoadMap(const AssetManagerPtr& assetManager, const std::string& fileName) {


}

void MapManagement::SaveMap(std::filesystem::path fileName) {


}
