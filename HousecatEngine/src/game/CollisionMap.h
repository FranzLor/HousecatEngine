#pragma once

#include <vector>

class CollisionMap {
public:
	CollisionMap() = default;
	~CollisionMap() = default;

	static std::vector<std::vector<bool>> collisionMap;

	static bool WalkableTiles(int x, int y);
};