#pragma once

#include <SDL.h>

#include <memory>

#include <sol/sol.hpp>

#include <vector>

#include "CollisionMap.h"

#include "../ecs/ECS.h"
#include "../assetmanager/AssetManager.h"


//----------------------------------------------------//
//                LEVEL MANAGER CLASS                 //
// Handles the dynamic creation of game levels using  //
//             data defined in Lua scripts.           //
//----------------------------------------------------//


class LevelManager {
private:
	std::vector<std::vector<bool>> collisionMap;
public:
	LevelManager();
	~LevelManager();

	void LoadLevel(const std::unique_ptr<Housecat>& housecat, SDL_Renderer* rendererGame, const std::unique_ptr<AssetManager>& assetManager, sol::state& lua, int level);
};




/**
 *
 * @class LevelManager
 * @brief Manages the loading and setup of game levels based on Lua script configuration.
 *
 * This class is responsible for interpreting Lua scripts that define level layouts, including tiles, entities,
 * and their components. It uses the provided Lua state to load and execute scripts which setup the game
 * environment dynamically.
 *
 * Usage:
 * - Level definitions are stored in Lua scripts, which include specifications for assets, tile maps,
 *   entities, and their components.
 * - The LevelManager loads these scripts, processes the contained data, and creates the game objects accordingly.
 *
 * Example:
 *   LevelManager levelManager;
 *   levelManager.LoadLevel(housecat, rendererGame, assetManager, lua, levelNumber);
 *
 * Key Methods:
 * - LoadLevel(...): Loads the specified level using the data defined in a Lua script. The method initializes
 *   game entities and their components, sets up the collision map, and can also initiate music and sound effects.
 * 
 * Note:
 * - Make sure the Lua script contains the necessary data for the level, including tile maps, entities, and components.
 * - Ensure that Lua libraries are opened and the Lua state is properly initialized before calling LoadLevel:
 *   `lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);`
 */