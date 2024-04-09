#include "CollisionMap.h"

#include <vector>

std::vector<std::vector<bool>> CollisionMap::collisionMap;

bool CollisionMap::WalkableTiles(int x, int y) {
    //out of bounds
    if (y < 0 || y >= static_cast<int>(collisionMap.size()) || x < 0 || x >= static_cast<int>(collisionMap[0].size())) {
        return false;
    }

    return !collisionMap[y][x];
}