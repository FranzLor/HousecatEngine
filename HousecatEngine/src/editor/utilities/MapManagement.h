#pragma once

#include <string>
#include <memory>
#include <sol/sol.hpp>
#include <filesystem>

#include "SDLUtility.h"

#include "../../assetmanager/AssetManager.h"
#include "../ui/EditorCanvas.h"

class MapManagement {
public:
	MapManagement() = default;
	~MapManagement() = default;

	void LoadMap(const AssetManagerPtr& assetManager, const std::string& fileName);
	void SaveMap(std::filesystem::path fileName);
};