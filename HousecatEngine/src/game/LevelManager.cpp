#include <fstream>
#include <string>
#include <sstream>

#include <sol/sol.hpp>

#include "Game.h"

#include "LevelManager.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/AnimationComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/HealthComponent.h"
#include "../components/UserControlComponent.h"
#include "../components/MovementStateComponent.h"
#include "../components/CameraComponent.h"
#include "../components/DamageAreaComponent.h"
#include "../components/TextDisplayComponent.h"
#include "../components/SFXComponent.h"
#include "../components/ScriptComponent.h"
#include "../components/WinConditionComponent.h"
#include <iomanip>

LevelManager::LevelManager() {}

LevelManager::~LevelManager() {}


//void LevelManager::LoadLevel(const std::unique_ptr<Housecat>& housecat, SDL_Renderer* rendererGame, const std::unique_ptr<AssetManager>& assetManager, sol::state& lua, int level) {
//	//load your lua script
//	sol::load_result luaScript = lua.load_file("./assets/scripts/NewScript.lua");
//	if (!luaScript.valid()) {
//		sol::error err = luaScript;
//		std::string errorMsg = err.what();
//		Logger::Error("Error loading Lua Script: " + errorMsg + "\nVerify File Name!");
//		return;
//	}
//
//	lua.script_file("./assets/scripts/NewScript.lua");
//
//	sol::table levelData = lua["project"];
//
//	sol::table assets = levelData["assets"];
//
//	//loop and read through lua data tables
//	int i = 0;
//	while (true) {
//		sol::optional<sol::table> hasAsset = assets[i];
//		if (hasAsset == sol::nullopt) {
//			break;
//		}
//		sol::table asset = assets[i];
//		std::string assetType = asset["type"];
//		if (assetType == "texture") {
//			assetManager->AddTexture(rendererGame, asset["id"], asset["file"]);
//		}
//		if (assetType == "font") {
//			assetManager->AddFont(asset["id"], asset["file"], asset["font_size"]);
//		}
//		if (assetType == "music") {
//			assetManager->AddMusic(asset["id"], asset["file"]);
//		}
//		if (assetType == "sound") {
//			assetManager->AddSound(asset["id"], asset["file"]);
//		}
//		i++;
//	}
//
//	// Load the map using the maps table
//	sol::table maps = levelData["maps"];
//	std::string mapFilePath = maps[0]["file_path"];
//	std::ifstream mapFile(mapFilePath);
//
//	if (!mapFile.is_open()) {
//		Logger::Error("Failed to open map file: " + mapFilePath);
//		return;
//	}
//
//	std::string line;
//	while (std::getline(mapFile, line)) {
//		std::istringstream iss(line);
//		std::string group, assetID;
//		int width, height, srcX, srcY, zIndex;
//		double posX, posY, scaleX, scaleY;
//
//		iss >> group >> std::quoted(assetID) >> width >> height >> srcX >> srcY >> zIndex >> posX >> posY >> scaleX >> scaleY;
//
//		if (iss.fail()) {
//			Logger::Error("Failed to parse line in map file: " + line);
//			continue;
//		}
//
//		Entity tile = housecat->CreateEntity();
//		tile.Group(group);
//		tile.AddComponent<TransformComponent>(glm::vec2(posX, posY), glm::vec2(scaleX, scaleY), 0.0);
//		tile.AddComponent<SpriteComponent>(assetID, width, height, zIndex, false, srcX, srcY);
//	}
//	mapFile.close();
//}

void LevelManager::LoadLevel(const std::unique_ptr<Housecat>& housecat, SDL_Renderer* rendererGame, const std::unique_ptr<AssetManager>& assetManager, sol::state& lua, int level) {
	//load lua script file
	sol::load_result luaScript = lua.load_file("./assets/scripts/TEST2.lua");
	if (!luaScript.valid()) {
		sol::error err = luaScript;
		std::string errorMsg = err.what();
		Logger::Error("Error loading Lua Script: " + errorMsg + "\nVerify File Name!");
		return;
	}

	lua.script_file("./assets/scripts/TEST2.lua");

	sol::table projectData = lua["project"];
	sol::table assets = projectData["assets"];
	sol::table canvas = projectData["canvas"];

	double tileScale = canvas.get_or("tile_scale", 1.0);
	int tileSize = canvas.get_or("tile_size", 16);
	int tileCols = canvas["canvas_width"];
	int tileRows = canvas["canvas_height"];

	//go over assets
	for (auto& asset_kv : assets) {
		sol::table asset = asset_kv.second.as<sol::table>();
		std::string asset_id = asset["asset_id"];
		std::string file_path = asset["file_path"];
		std::string type = asset.get_or("type", std::string("texture"));

		if (type == "font") {
			int font_size = asset["font_size"];
			assetManager->AddFont(asset_id, file_path, font_size);
		}
		else if (type == "music") {
			assetManager->AddMusic(asset_id, file_path);
		}
		else if (type == "sound") {
			assetManager->AddSound(asset_id, file_path);
		}
		else {
			//default to adding a texture if no specific type is found
			assetManager->AddTexture(rendererGame, asset_id, file_path);
		}
	}

	sol::table maps = projectData["maps"];
	std::string mapFilePath = maps[0]["file_path"];
	std::ifstream mapFile(mapFilePath);
	if (!mapFile.is_open()) {
		Logger::Error("Failed to open map file: " + mapFilePath);
		return;
	}

	std::string line;
	while (std::getline(mapFile, line)) {
		std::istringstream iss(line);
		std::string group, assetID;
		int width, height, srcX, srcY, zIndex;
		double posX, posY, scaleX, scaleY;

		iss >> group >> std::quoted(assetID) >> width >> height >> srcX >> srcY >> zIndex >> posX >> posY >> scaleX >> scaleY;

		if (iss.fail()) {
			Logger::Error("Failed to parse line in map file: " + line);
			continue;
		}

		Entity tile = housecat->CreateEntity();
		tile.Group(group);
		tile.AddComponent<TransformComponent>(glm::vec2(posX * tileScale, posY * tileScale), glm::vec2(scaleX * tileScale, scaleY * tileScale), 0.0);
		tile.AddComponent<SpriteComponent>(assetID, width, height, zIndex, false, srcX, srcY);
	}
	mapFile.close();

	Game::mapWidth = static_cast<int>(tileCols * tileSize * tileScale);
	Game::mapHeight = static_cast<int>(tileRows * tileSize * tileScale);
	Game::tileSize = tileSize;
	Game::tileScale = tileScale;
}





	//sol::table map = levelData["tilemap"];
	//std::string mapFilePath = map["mapFilePath"];
	//std::string textureID = map["textureID"];

	//int tileSize = map["tileSize"];
	//double tileScale = map["tileScale"];
	//int tileCols = map["tileCols"];
	//int tileRows = map["tileRows"];
	////for tileset
	//const int tilePerRow = map["tilePerRow"];

	//std::fstream mapFile(mapFilePath);
	//std::string line;
	////counter row
	//int y = 0;

	//CollisionMap::collisionMap.resize(tileRows, std::vector<bool>(tileCols, false));

	//while (std::getline(mapFile, line) && y < tileRows) {
	//	std::istringstream lineStream(line);
	//	std::string tileCode;

	//	//counter col
	//	int x = 0;
	//	while (std::getline(lineStream, tileCode, ',') && x < tileCols) {
	//		int tileType = std::stoi(tileCode);

	//		int srcRectX = (tileType % tilePerRow) * tileSize;
	//		int srcRectY = (tileType / tilePerRow) * tileSize;

	//		Entity tile = housecat->CreateEntity();
	//		tile.Group("tilemap");
	//		tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
	//		tile.AddComponent<SpriteComponent>(textureID, tileSize, tileSize, 0, false, srcRectX, srcRectY);

	//		//define nonwalkable tiles
	//		if (tileCode == "55") {
	//			CollisionMap::collisionMap[y][x] = true;
	//		}
	//		x++;
	//	}
	//	y++;
	//}
	//mapFile.close();

	//Game::mapWidth = static_cast<int>(tileCols * tileSize * tileScale);
	//Game::mapHeight = static_cast<int>(tileRows * tileSize * tileScale);
	//Game::tileSize = tileSize;
	//Game::tileScale = tileScale;

	//NOTE

	//mapwidth: 2240px
	//mapheight: 2560px


	







	/////////////////////////////////////////////////////










	//sol::table entities = levelData["entities"];
	//i = 0;
	//while (true) {
	//	sol::optional<sol::table> hasEntity = entities[i];
	//	if (hasEntity == sol::nullopt) {
	//		break;
	//	}

	//	sol::table entity = entities[i];

	//	Entity newEntity = housecat->CreateEntity();

	//	//tag
	//	sol::optional<std::string> tag = entity["tag"];
	//	if (tag != sol::nullopt) {
	//		newEntity.Tag(entity["tag"]);
	//	}

	//	//group
	//	sol::optional<std::string> group = entity["group"];
	//	if (group != sol::nullopt) {
	//		newEntity.Group(entity["group"]);
	//	}

	//	//components
	//	sol::optional<sol::table> hasComponents = entity["components"];
	//	if (hasComponents != sol::nullopt) {
	//		//usercontrol
	//		sol::optional<sol::table> userController = entity["components"]["userControl"];
	//		if (userController != sol::nullopt) {
	//			newEntity.AddComponent<UserControlComponent>(
	//				glm::vec2(
	//					entity["components"]["userControl"]["up"]["x"],
	//					entity["components"]["userControl"]["up"]["y"]
	//				),
	//				glm::vec2(
	//					entity["components"]["userControl"]["right"]["x"],
	//					entity["components"]["userControl"]["right"]["y"]
	//				),
	//				glm::vec2(
	//					entity["components"]["userControl"]["down"]["x"],
	//					entity["components"]["userControl"]["down"]["y"]
	//				),
	//				glm::vec2(
	//					entity["components"]["userControl"]["left"]["x"],
	//					entity["components"]["userControl"]["left"]["y"]
	//				)
	//			);
	//		}

	//		//transform
	//		sol::optional<sol::table> transform = entity["components"]["transform"];
	//		if (transform != sol::nullopt) {
	//			newEntity.AddComponent<TransformComponent>(
	//				glm::vec2(
	//					entity["components"]["transform"]["position"]["x"],
	//					entity["components"]["transform"]["position"]["y"]
	//				),
	//				glm::vec2(
	//					entity["components"]["transform"]["scale"]["x"].get_or(1.0),
	//					entity["components"]["transform"]["scale"]["y"].get_or(1.0)
	//				),
	//				entity["components"]["transform"]["rotation"].get_or(0.0)
	//			);
	//		}

	//		//sprite
	//		sol::optional<sol::table> sprite = entity["components"]["sprite"];
	//		if (sprite != sol::nullopt) {
	//			newEntity.AddComponent<SpriteComponent>(
	//				entity["components"]["sprite"]["textureID"],
	//				entity["components"]["sprite"]["width"],
	//				entity["components"]["sprite"]["height"],
	//				entity["components"]["sprite"]["zIndex"].get_or(1),
	//				entity["components"]["sprite"]["fixed"].get_or(false),
	//				entity["components"]["sprite"]["srcRectX"].get_or(0),
	//				entity["components"]["sprite"]["srcRectY"].get_or(0),
	//				entity["components"]["sprite"]["flip"].get_or(0)
	//			);
	//		}

	//		//rigidbody
	//		sol::optional<sol::table> rigidbody = entity["components"]["rigidbody"];
	//		if (rigidbody != sol::nullopt) {
	//			newEntity.AddComponent<RigidBodyComponent>(
	//				glm::vec2(
	//					entity["components"]["rigidbody"]["velocity"]["x"].get_or(0.0),
	//					entity["components"]["rigidbody"]["velocity"]["y"].get_or(0.0)
	//				)
	//			);
	//		}

	//		//animation
	//		sol::optional<sol::table> animation = entity["components"]["animation"];
	//		if (animation != sol::nullopt) {
	//			newEntity.AddComponent<AnimationComponent>(
	//				entity["components"]["animation"]["numFrames"].get_or(1),
	//				entity["components"]["animation"]["frameSpeed"].get_or(1),
	//				entity["components"]["animation"]["looped"].get_or(true)
	//			);
	//		}

	//		//movementstate
	//		sol::optional<sol::table> movement = entity["components"]["movementState"];
	//		if (movement != sol::nullopt) {
	//			newEntity.AddComponent<MovementStateComponent>(
	//				entity["components"]["movementState"]["isMoving"].get_or(false)
	//			);
	//		}

	//		//boxcollider
	//		sol::optional<sol::table> collider = entity["components"]["boxcollider"];
	//		if (collider != sol::nullopt) {
	//			newEntity.AddComponent<BoxColliderComponent>(
	//				entity["components"]["boxcollider"]["width"],
	//				entity["components"]["boxcollider"]["height"],
	//				glm::vec2(
	//					entity["components"]["boxcollider"]["offset"]["x"].get_or(0),
	//					entity["components"]["boxcollider"]["offset"]["y"].get_or(0)
	//				)
	//			);
	//		}

	//		//health
	//		sol::optional<sol::table> health = entity["components"]["health"];
	//		if (health != sol::nullopt) {

	//			//lambda for extracting SDL color from lua table / default
	//			auto getcolor = [](const sol::table& table, const std::string& key, SDL_Color defaultColor) -> SDL_Color {
	//				sol::optional<sol::table> colorTable = table[key];
	//				if (!colorTable) return defaultColor;

	//				//init to white
	//				SDL_Color color = { 255, 255, 255, 255 };

	//				color.r = (*colorTable).get_or("r", defaultColor.r);
	//				color.g = (*colorTable).get_or("g", defaultColor.g);
	//				color.b = (*colorTable).get_or("b", defaultColor.b);
	//				color.a = (*colorTable).get_or("a", defaultColor.a);
	//				return color;
	//			};

	//			//applying lambda function to extract SDL_Color vals
	//			SDL_Color lowHealth = getcolor(*health, "lowHealth", { 255, 0, 0, 255 });
	//			SDL_Color mediumHealth = getcolor(*health, "mediumHealth", { 255, 255, 0, 255 });
	//			SDL_Color highHealth = getcolor(*health, "highHealth", { 0, 255, 0, 255 });

	//			newEntity.AddComponent<HealthComponent>(
	//				static_cast<int>(entity["components"]["health"]["healthPercent"].get_or(100)),
	//				entity["components"]["health"]["allowText"].get_or(false),

	//				lowHealth,
	//				mediumHealth,
	//				highHealth,

	//				entity["components"]["health"]["healthBarWidth"].get_or(35),
	//				entity["components"]["health"]["healthBarHeight"].get_or(5),
	//				entity["components"]["health"]["horizontalOffset"].get_or(65),
	//				entity["components"]["health"]["verticalOffset"].get_or(0)
	//			);
	//		}

	//		//camera
	//		sol::optional<sol::table> cameraFollow = entity["components"]["camera"];
	//		if (cameraFollow != sol::nullopt) {
	//			newEntity.AddComponent<CameraComponent>();
	//		}

	//		//damageArea
	//		sol::optional<sol::table> damageArea = entity["components"]["damageArea"];
	//		if (damageArea != sol::nullopt) {
	//			newEntity.AddComponent<DamageAreaComponent>(
	//				entity["components"]["damageArea"]["isFriendly"].get_or(false),
	//				entity["components"]["damageArea"]["hitDamage"].get_or(1),
	//				entity["components"]["damageArea"]["damageDelay"].get_or(1.0)
	//			);
	//		}

	//		//SFX
	//		sol::optional<sol::table> sfx = entity["components"]["sfx"];
	//		if (sfx != sol::nullopt) {
	//			newEntity.AddComponent<SFXComponent>(
	//				entity["components"]["sfx"]["sfxID"],
	//				entity["components"]["sfx"]["volume"].get_or(50),
	//				entity["components"]["sfx"]["loop"].get_or(0),
	//				entity["component"]["sfx"]["isPlaying"].get_or(false),
	//				entity["components"]["sfx"]["delay"].get_or(2)
	//			);
	//		}

	//		//SCRIPT
	//		sol::optional<sol::table> script = entity["components"]["script"];
	//		if (script != sol::nullopt) {
	//			sol::function function = entity["components"]["script"][0];
	//			newEntity.AddComponent<ScriptComponent>(function);
	//		}

	//		//WIN CONDITION 
	//		sol::optional<sol::table> winning = entity["components"]["winning"];
	//		if (winning != sol::nullopt) {
	//			newEntity.AddComponent<WinConditionComponent>();
	//		}

	//		//TEXT
	//		sol::optional<sol::table> text = entity["components"]["text"];
	//		if (text != sol::nullopt) {
	//			newEntity.AddComponent<TextDisplayComponent>(
	//				entity["components"]["text"]["fontID"],
	//				glm::vec2(
	//					entity["components"]["text"]["position"]["x"],
	//					entity["components"]["text"]["position"]["y"]
	//				),

	//				entity["components"]["text"]["isFixed"].get_or(true),
	//				entity["components"]["text"]["isVisible"].get_or(true),
	//				entity["components"]["text"]["text"],

	//				SDL_Color{
	//					entity["components"]["text"]["color"]["r"],
	//					entity["components"]["text"]["color"]["g"],
	//					entity["components"]["text"]["color"]["b"],
	//					entity["components"]["text"]["color"]["a"]
	//				}
	//			);
	//		}
	//	}
	//	i++;
	//}
//}