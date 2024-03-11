#pragma once

#include <SDL.h>

#include <memory>

#include "../ecs/ECS.h"
#include "../assetmanager/AssetManager.h"

class LevelManager {
public:
	LevelManager();
	~LevelManager();

	void LoadLevel();
};