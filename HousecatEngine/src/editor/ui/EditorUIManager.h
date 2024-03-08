#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileAttributes.h"
#include "EditorCanvas.h"

#include "../utilities/SDLUtility.h"
#include "../editmanager/EditManager.h"

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


public:
	EditorUIManager();
	~EditorUIManager();

	//TODO
	//ImGui
	void InitImGui();

	//TODO
	//project management
	void ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, int& tileSize);

	void ShowEditMenu();

	void ShowViewMenu();

	void ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager);

	//TODO
	//file management
	void NewProject();

	void OpenProject(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, int& tileSize);

	void Save(EditorRenderer& renderer, const AssetManagerPtr& assetManager, const int& canvasWidth, const int& canvasHeight, int& tileSize);

	//TODO
	//tileset management
	void TileAttributes(const AssetManagerPtr& assetManager);

	void SetTileset(const AssetManagerPtr& assetManager);

	//TODO
	//shortcut management
	void ApplyShortcuts();
};


