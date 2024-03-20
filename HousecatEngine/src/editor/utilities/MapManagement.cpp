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
	std::fstream mapFile;
	mapFile.open(fileName);

	if (!mapFile.is_open()) {
		//REMIND
		//for now
		std::cerr << "Error: Failed to Open File " << fileName << std::endl;
		return;
	}

	std::string group;
	std::string assetID;
	int tileWidth;
	int tileHeight;
	int srcRectX;
	int srcRectY;
	int layer;

	double rotation;

	glm::vec2 transform;
	glm::vec2 scale;


	while (mapFile >> group >> assetID >> tileWidth >> tileHeight >> srcRectX >> srcRectY >> 
		layer >> rotation >> transform.x >> transform.y >> scale.x >> scale.y) {

		Entity tile = Housecat::GetInstance().CreateEntity();
		tile.Group(group);
		tile.AddComponent<TransformComponent>(transform, scale, rotation);
		tile.AddComponent<SpriteComponent>(assetID, tileWidth, tileHeight, layer, srcRectX, srcRectY);

	}
	mapFile.close();
}

void MapManagement::SaveMap(std::filesystem::path fileName) {
	if (!Housecat::GetInstance().IsThereGroup("tiles")) {
		return;
	}

	std::ofstream mapFile(fileName);
	if (!mapFile.is_open()) {
		return;
	}

	auto tiles = Housecat::GetInstance().GetGroup("tiles");

	for (const auto& tile : tiles) {
		const auto& transform = tile.GetComponent<TransformComponent>();
		const auto& sprite = tile.GetComponent<SpriteComponent>();

		mapFile << "tiles" << " " << sprite.assetID << " " << sprite.width << " " << sprite.height << " "
			<< sprite.srcRect.x << " " << sprite.srcRect.y << " " << sprite.zIndex << " " << transform.rotation
			<< " " << transform.position.x << " " << transform.position.y << " " << transform.scale.x << " " << transform.scale.y << "\n";

	}
}
