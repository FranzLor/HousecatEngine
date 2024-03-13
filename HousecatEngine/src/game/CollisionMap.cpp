#include "CollisionMap.h"

#include <vector>

std::vector<std::vector<bool>> CollisionMap::collisionMap;

bool CollisionMap::WalkableTiles(int x, int y) {
    //out of bounds
    if (y < 0 || y >= collisionMap.size() || x < 0 || x >= collisionMap[0].size()) {
        return false;
    }

    return !collisionMap[y][x];
}