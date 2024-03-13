#include <fstream>

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

LevelManager::LevelManager() {}

LevelManager::~LevelManager() {}

void LevelManager::LoadLevel(const std::unique_ptr<Housecat>& housecat, SDL_Renderer* rendererGame, const std::unique_ptr<AssetManager>& assetManager, sol::state& lua, int level) {
	
	//TODO
	//REMIND
	//("Level1Test.lua") is a placeholder for now -> ("./assets/scripts/Level" + to_string(level) + ".lua")
	sol::load_result luaScript = lua.load_file("./assets/scripts/Level1Test.lua");
	if (!luaScript.valid()) {
		sol::error err = luaScript;
		std::string errorMsg = err.what();
		Logger::Error("Error loading Lua Script: " + errorMsg);
		return;
	}

	lua.script_file("./assets/scripts/Level1Test.lua");

	sol::table levelData = lua["Level"];

	sol::table assets = levelData["assets"];

	//loop and read through lua data tables
	int i = 0;
	while (true) {
		sol::optional<sol::table> hasAsset = assets[i];
		if (hasAsset == sol::nullopt) {
			break;
		}
		sol::table asset = assets[i];
		std::string assetType = asset["type"];
		if (assetType == "texture") {
			assetManager->AddTexture(rendererGame, asset["id"], asset["file"]);
		}
		if (assetType == "font") {
			assetManager->AddFont(asset["id"], asset["file"], asset["font_size"]);
		}
		i++;
	}




	/////////////////////////////////////////////////////





	sol::table map = levelData["tilemap"];

	std::string mapFilePath = map["mapFilePath"];
	std::string textureID = map["textureID"];

	int tileSize = map["tileSize"];
	double tileScale = map["tileScale"];
	int tileCols = map["tileCols"];
	int tileRows = map["tileRows"];

	std::fstream mapFile;

	mapFile.open(mapFilePath);
	for (int y = 0; y < tileRows; y++) {
		for (int x = 0; x < tileCols; x++) {
			char ch;
			mapFile.get(ch);
			int srcRectY = std::atoi(&ch) * tileSize;

			mapFile.get(ch);
			int srcRectX = std::atoi(&ch) * tileSize;
			mapFile.ignore();
			mapFile.ignore();

			Entity tile = housecat->CreateEntity();
			tile.Group("tilemap");
			tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
			tile.AddComponent<SpriteComponent>(textureID, tileSize, tileSize, 0, false, srcRectX, srcRectY);


		}
	}
	mapFile.close();

	Game::mapWidth = static_cast<int>(tileCols * tileSize * tileScale);
	Game::mapHeight = static_cast<int>(tileRows * tileSize * tileScale);

	//NOTE

	//mapwidth: 2240px
	//mapheight: 2560px



	/////////////////////////////////////////////////////




	sol::table entities = levelData["entities"];
	i = 0;
	while (true) {
		sol::optional<sol::table> hasEntity = entities[i];
		if (hasEntity == sol::nullopt) {
			break;
		}

		sol::table entity = entities[i];

		Entity newEntity = housecat->CreateEntity();

		//tag
		sol::optional<std::string> tag = entity["tag"];
		if (tag != sol::nullopt) {
			newEntity.Tag(entity["tag"]);
		}

		//group
		sol::optional<std::string> group = entity["group"];
		if (group != sol::nullopt) {
			newEntity.Group(entity["group"]);
		}

		//components
		sol::optional<sol::table> hasComponents = entity["components"];
		if (hasComponents != sol::nullopt) {
			//usercontrol
			sol::optional<sol::table> userController = entity["components"]["userControl"];
			if (userController != sol::nullopt) {
				newEntity.AddComponent<UserControlComponent>(
					glm::vec2(
						entity["components"]["userControl"]["up"]["x"],
						entity["components"]["userControl"]["up"]["y"]
					),
					glm::vec2(
						entity["components"]["userControl"]["right"]["x"],
						entity["components"]["userControl"]["right"]["y"]
					),
					glm::vec2(
						entity["components"]["userControl"]["down"]["x"],
						entity["components"]["userControl"]["down"]["y"]
					),
					glm::vec2(
						entity["components"]["userControl"]["left"]["x"],
						entity["components"]["userControl"]["left"]["y"]
					)
				);
			}

			//transform
			sol::optional<sol::table> transform = entity["components"]["transform"];
			if (transform != sol::nullopt) {
				newEntity.AddComponent<TransformComponent>(
					glm::vec2(
						entity["components"]["transform"]["position"]["x"],
						entity["components"]["transform"]["position"]["y"]
					),
					glm::vec2(
						entity["components"]["transform"]["scale"]["x"].get_or(1.0),
						entity["components"]["transform"]["scale"]["y"].get_or(1.0)
					),
					entity["components"]["transform"]["rotation"].get_or(0.0)
				);
			}

			//sprite
			sol::optional<sol::table> sprite = entity["components"]["sprite"];
			if (sprite != sol::nullopt) {
				newEntity.AddComponent<SpriteComponent>(
					entity["components"]["sprite"]["textureID"],
					entity["components"]["sprite"]["width"],
					entity["components"]["sprite"]["height"],
					entity["components"]["sprite"]["zIndex"].get_or(1),
					entity["components"]["sprite"]["fixed"].get_or(false),
					entity["components"]["sprite"]["srcRectX"].get_or(0),
					entity["components"]["sprite"]["srcRectY"].get_or(0)
				);
			}

			//rigidbody
			sol::optional<sol::table> rigidbody = entity["components"]["rigidbody"];
			if (rigidbody != sol::nullopt) {
				newEntity.AddComponent<RigidBodyComponent>(
					glm::vec2(
						entity["components"]["rigidbody"]["velocity"]["x"].get_or(0.0),
						entity["components"]["rigidbody"]["velocity"]["y"].get_or(0.0)
					)
				);
			}

			//animation
			sol::optional<sol::table> animation = entity["components"]["animation"];
			if (animation != sol::nullopt) {
				newEntity.AddComponent<AnimationComponent>(
					entity["components"]["animation"]["numFrames"].get_or(1),
					entity["components"]["animation"]["frameSpeed"].get_or(1),
					entity["components"]["animation"]["looped"].get_or(true)
				);
			}

			//movementstate
			sol::optional<sol::table> movement = entity["components"]["movementState"];
			if (movement != sol::nullopt) {
				newEntity.AddComponent<MovementStateComponent>(
					entity["components"]["movementState"]["isMoving"].get_or(false)
				);
			}

			//boxcollider
			sol::optional<sol::table> collider = entity["components"]["boxcollider"];
			if (collider != sol::nullopt) {
				newEntity.AddComponent<BoxColliderComponent>(
					entity["components"]["boxcollider"]["width"],
					entity["components"]["boxcollider"]["height"],
					glm::vec2(
						entity["components"]["boxcollider"]["offset"]["x"].get_or(0),
						entity["components"]["boxcollider"]["offset"]["y"].get_or(0)
					)
				);
			}

			//health
			sol::optional<sol::table> health = entity["components"]["health"];
			if (health != sol::nullopt) {
				newEntity.AddComponent<HealthComponent>(
					static_cast<int>(entity["components"]["health"]["healthPercent"].get_or(100))
				);
			}

			//camera
			sol::optional<sol::table> cameraFollow = entity["components"]["camera"];
			if (cameraFollow != sol::nullopt) {
				newEntity.AddComponent<CameraComponent>();
			}

			//damageArea
			sol::optional<sol::table> damageArea = entity["components"]["damageArea"];
			if (damageArea != sol::nullopt) {
				newEntity.AddComponent<DamageAreaComponent>(
					entity["components"]["damageArea"]["isFriendly"].get_or(false),
					entity["components"]["damageArea"]["hitDamage"].get_or(1),
					entity["components"]["damageArea"]["damageDelay"].get_or(1.0)
				);
			}
		}
		i++;
	}
}




//----------------------------------------------------//
//              TESTING for ref                       //
//----------------------------------------------------//
	//ASSETS - add textures to game
	//assetManager->AddTexture(rendererGame, "player", "./assets/textures/cat_sprite_2.png");

	//assetManager->AddTexture(rendererGame, "npc", "./assets/textures/cat_animate_2.png");

	//assetManager->AddTexture(rendererGame, "cat_run", "./assets/textures/cat_run.png");
	////assetManager->AddTexture(rendererGame, "cat2", "./assets/textures/cat_ex.png");

	//assetManager->AddTexture(rendererGame, "ghost", "./assets/textures/ghost.png");

	//assetManager->AddTexture(rendererGame, "chest", "./assets/textures/chest_test.png");

	//assetManager->AddTexture(rendererGame, "fire", "./assets/textures/fire_sprite.png");

	//assetManager->AddTexture(rendererGame, "map", "./assets/tilemaps/terrain_tile.png");

	//assetManager->AddFont("roboto", "./assets/fonts/roboto.regular.ttf", 18);
	//assetManager->AddFont("montserrat", "./assets/fonts/montserrat.bold.ttf", 20);


	////load tilemap test
	//int tileSize = 32;
	//double tileScale = 2.0;
	//int mapColumns = 40;
	//int mapRows = 40;

	//std::fstream mapFile;

	////TODO error handling?
	//mapFile.open("./assets/tilemaps/map_test.map");

	//for (int y = 0; y < mapRows; y++) {
	//	for (int x = 0; x < mapColumns; x++) {
	//		char ch;
	//		mapFile.get(ch);
	//		int srcRectY = std::atoi(&ch) * tileSize;

	//		mapFile.get(ch);
	//		int srcRectX = std::atoi(&ch) * tileSize;
	//		mapFile.ignore();
	//		mapFile.ignore();

	//		Entity tile = housecat->CreateEntity();
	//		tile.Group("tilemap");
	//		tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
	//		tile.AddComponent<SpriteComponent>("map", tileSize, tileSize, 0, false, srcRectX, srcRectY);

	//	}
	//}
	//mapFile.close();

	//Game::mapWidth = static_cast<int>(mapColumns * tileSize * tileScale);
	//Game::mapHeight = static_cast<int>(mapRows * tileSize * tileScale);



	////TODO: lua
	////ENTITIES - create entities to game
	//Entity cat1 = housecat->CreateEntity();
	//Entity cat2 = housecat->CreateEntity();
	//Entity cat3 = housecat->CreateEntity();
	//Entity cat4 = housecat->CreateEntity();

	//Entity player = housecat->CreateEntity();
	//Entity ghost = housecat->CreateEntity();

	//Entity chestR = housecat->CreateEntity();
	//Entity chestL = housecat->CreateEntity();
	//Entity fire = housecat->CreateEntity();

	//Entity healthLabel = housecat->CreateEntity();

	////TODO: lua
	////COMPONENTS - add components to entities

	////housecat->AddComponent<TransformComponent>(cat1, glm::vec2(250.0, 250.0), glm::vec2(1.0, 1.0), 0.0);

	////TESTING GROUNDS
	//player.Tag("player");
	//player.AddComponent<UserControlComponent>(glm::vec2(0, -90), glm::vec2(90, 0), glm::vec2(0, 90), glm::vec2(-90, 0));
	//player.AddComponent<TransformComponent>(glm::vec2(180, 500), glm::vec2(4.0, 4.0), 0.0);
	//player.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	//player.AddComponent<AnimationComponent>(4, 5, true);
	//player.AddComponent<MovementStateComponent>(false);
	//player.AddComponent<SpriteComponent>("player", 32, 32, 2);
	//player.AddComponent<HealthComponent>(100);
	//player.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(20.0, 24.0));
	//player.AddComponent<CameraComponent>();

	//cat1.Group("npc");
	//cat1.AddComponent<TransformComponent>(glm::vec2(150, 250), glm::vec2(4.0, 4.0), 0.0);
	//cat1.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	//cat1.AddComponent<AnimationComponent>(4, 5, true);
	//cat1.AddComponent<MovementStateComponent>(true);
	//cat1.AddComponent<SpriteComponent>("npc", 32, 32, 3);
	//cat1.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(20.0, 24.0));

	//cat2.Group("npc");
	//cat2.AddComponent<TransformComponent>(glm::vec2(90, 295), glm::vec2(2.0, 2.0), 0.0);
	//cat2.AddComponent<AnimationComponent>(4, 8, true);
	//cat2.AddComponent<MovementStateComponent>(true);
	//cat2.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	//cat2.AddComponent<SpriteComponent>("npc", 32, 32, 2);
	//cat2.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(10.0, 16.0));

	//cat3.Group("npc");
	//cat3.AddComponent<TransformComponent>(glm::vec2(160, 270), glm::vec2(2.0, 2.0), 0.0);
	//cat3.AddComponent<AnimationComponent>(4, 8, true);
	//cat3.AddComponent<MovementStateComponent>(true);
	//cat3.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	//cat3.AddComponent<SpriteComponent>("npc", 32, 32, 2);
	//cat3.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(10.0, 16.0));

	//cat4.Group("npc");
	//cat4.AddComponent<TransformComponent>(glm::vec2(140, 315), glm::vec2(2.0, 2.0), 0.0);
	//cat4.AddComponent<AnimationComponent>(4, 8, true);
	//cat4.AddComponent<MovementStateComponent>(true);
	//cat4.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	//cat4.AddComponent<SpriteComponent>("npc", 32, 32, 4);
	//cat4.AddComponent<BoxColliderComponent>(22, 20, glm::vec2(10.0, 16.0));


	//ghost.Group("enemy");
	//ghost.AddComponent<TransformComponent>(glm::vec2(540, 400), glm::vec2(2.0, 2.0), 0.0);
	//ghost.AddComponent<AnimationComponent>(10, 10, true);
	//ghost.AddComponent<MovementStateComponent>(true);
	//ghost.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	//ghost.AddComponent<SpriteComponent>("ghost", 32, 32, 4);
	//ghost.AddComponent<BoxColliderComponent>(32, 32);
	//ghost.AddComponent<DamageAreaComponent>(false, 20);

	//fire.Group("hazards");
	//fire.AddComponent<TransformComponent>(glm::vec2(200, 700), glm::vec2(5.0, 5.0), 0.0);
	//fire.AddComponent<MovementStateComponent>(true);
	//fire.AddComponent<AnimationComponent>(8, 10, true);
	//fire.AddComponent<SpriteComponent>("fire", 24, 32, 4);
	//fire.AddComponent<BoxColliderComponent>(15, 5, glm::vec2(25, 32 * 4.2));
	//fire.AddComponent<DamageAreaComponent>(false, 20, 1.0);


	//chestR.Group("barriers");
	//chestR.AddComponent<TransformComponent>(glm::vec2(400, 280), glm::vec2(3.0, 3.0), 0.0);
	//chestR.AddComponent<SpriteComponent>("chest", 37, 32, 5);
	//chestR.AddComponent<BoxColliderComponent>(37, 32);

	//chestL.Group("barriers");
	//chestL.AddComponent<TransformComponent>(glm::vec2(0, 280), glm::vec2(3.0, 3.0), 0.0);
	//chestL.AddComponent<SpriteComponent>("chest", 37, 32, 5);
	//chestL.AddComponent<BoxColliderComponent>(37, 32);

	//SDL_Color red = { 255, 0, 0 };
	//healthLabel.AddComponent<TextDisplayComponent>("montserrat", glm::vec2(5, 5), true, "Housecat", red);