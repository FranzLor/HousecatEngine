#pragma once

#include <vector>


//----------------------------------------------------//
//                  COLLISION MAP                     //
//   Manages collision data for game environments.    //
//----------------------------------------------------//


class CollisionMap {
public:
	CollisionMap() = default;
	~CollisionMap() = default;

	static std::vector<std::vector<bool>> collisionMap;

	static bool WalkableTiles(int x, int y);
};




/**
 *
 * @class CollisionMap
 * @brief Manages a grid of boolean values where each value represents whether a tile is walkable or blocked.
 *
 * This class facilitates the collision detection system by providing a simple interface to query the walkability of tiles in a game map.
 * The static member `collisionMap` holds a grid of booleans indicating walkable (false) and blocked (true) tiles.
 *
 * Usage:
 * - Initialize the collisionMap with dimensions and values according to your game map at the start.
 * - Query the collisionMap to determine if a tile is walkable or not, aiding in navigation and movement mechanics.
 *
 * Example:
 *	std::vector<std::vector<bool>> mapData = {
 *	  {false, false, true},
 *	  {false, true, true},
 *	  {false, false, false}
 *	};
 *	CollisionMap::collisionMap = mapData;
 * 
 *  Setting up a collision map
 *
 *	bool canWalk = CollisionMap::WalkableTiles(1, 1);
 * 
 *  Checking if a tile at (1,1) is walkable
 *
 * Key Methods:
 * - WalkableTiles(int x, int y): Returns true if the tile at the specified x and y coordinates is walkable.
 *
 * This system is crucial for games with tile-based movement or navigation, ensuring entities interact with the game world's physical properties accurately.
 *
 */