#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileAttributes.h"
#include "EditorCanvas.h"

#include "../utilities/SDLUtility.h"
#include "../utilities/editmanager/EditManager.h"
#include "../utilities/mouse/Mouse.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"

class EditorUIManager {
private:
	//tile
	TileAttributes tileAttributes;
	TileAttributes tilePrevAttributes;
	int tileWidth;
	int tileHeight;
	int textureWidth;
	int textureHeight;
	bool isImageLoaded;

	//edit
	bool Undo;
	bool Redo;

	//project
	std::string file;
	std::string assetID;

	//tilesets
	std::vector<std::string> tilesets;
	std::vector<std::string> tilesetsTarget;

	std::unique_ptr<class EditManager> editManager;

	std::shared_ptr<class Mouse> mouse;

public:
	EditorUIManager(class std::shared_ptr<Mouse>& mouse);
	~EditorUIManager();

	//TODO
	//ImGui
	void InitImGui();

	void Setup();

	//TODO
	//project management
	void ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, int& tileSize);

	void ShowEditMenu();

	void ShowViewMenu();

	void ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse);

	//TODO
	//file management
	void NewProject();

	void OpenProject(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, int& tileSize);

	void Save(EditorRenderer& renderer, const AssetManagerPtr& assetManager, const int& canvasWidth, const int& canvasHeight, int& tileSize);

	//TODO
	//tileset management
	void TilesetWindow(const AssetManagerPtr& assetManager, const glm::vec2& mouseRect);

	void TilesetLayers(const AssetManagerPtr& assetManager);

	void TileAttributes(const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse);

	//TODO
	//shortcut management
	void ApplyShortcuts();
};


