#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileAttributes.h"
#include "EditorCanvas.h"

#include "../utilities/SDLUtility.h"
#include "../utilities/editmanager/EditManager.h"
#include "../utilities/mouse/Mouse.h"
#include "../utilities/FileDialogue.h"
#include "../utilities/ProjectManagement.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"

class EditorUIManager {
private:
	int tileWidth;
	int tileHeight;
	int textureWidth;
	int textureHeight;

	bool loadTileset;
	bool isReset;
	bool isNewFile;
	bool newCanvas;

	bool tilesetLoaded;

	//tileset tools
	bool isPaintToolActive;
	bool isEraserToolActive;
	bool isFillToolActive;

	const int titleBar = 25;

	//edit
	bool Undo;
	bool Redo;

	//exit
	bool isExit;

	//tile
	TileAttributes tileAttributes;
	TileAttributes tilePrevAttributes;


	//project
	std::string fileName;
	std::string assetID;
	std::string imageName;
	std::string luaFile;

	//tilesets
	std::vector<std::string> tilesets;
	std::vector<std::string> tilesetsTarget;

	std::unique_ptr<class FileDialogue> fileDialog;
	std::unique_ptr<class ProjectManagement> projectManagement;

	std::shared_ptr<class Mouse> mouse;

public:
	EditorUIManager(class std::shared_ptr<Mouse>& mouse);
	~EditorUIManager();

	//TODO
	//ImGui
	void InitImGui();

	//TODO
	//project management
	void ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, sol::state& lua, int& tileSize);

	void ShowEditMenu();

	void ShowViewMenu();

	void ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager);

	//TODO
	//file management
	void NewProject();

	void Open(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<EditorCanvas>& canvas, sol::state& lua, int& tileSize);

	void Save(EditorRenderer& renderer, const AssetManagerPtr& assetManager, const int& canvasWidth, const int& canvasHeight, int& tileSize);

	void OpenNewWindow();

	void ResetLoadedFiles();

	const bool& IsTilesetLoaded() const {
		return tilesetLoaded;
	}

	inline const bool& FileReset() const {
		return isReset;
	}

	inline void SetFileReset(const bool& reset) {
		isReset = reset;
	}

	//tools getter
	inline const bool& IsPaintToolActive() const {
		return isPaintToolActive;
	}

	inline const bool& IsEraserToolActive() const {
		return isEraserToolActive;
	}

	inline const bool& IsFillToolActive() const {
		return isFillToolActive;
	}

	//TODO
	//tileset management
	void TilesetWindow(const AssetManagerPtr& assetManager, const glm::vec2& mouseRect);

	void TilesetTools(const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse, bool tileWindow);

	void TilesetLayers(const AssetManagerPtr& assetManager);

	void TileAttributes(const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse, bool tileWindow);

	//TODO
	//shortcut management
	void Shortcuts(EditorRenderer& renderer,  const AssetManagerPtr& assetManager,
		std::shared_ptr<EditorCanvas>& canvas, const std::unique_ptr<EditManager>& editManager, int& tileSize, sol::state& lua);

	
	//exit
	const bool& GetExit() const {
		return isExit;
	}


	//comopnents
	bool CheckTransform();

	bool CheckSprite();
};


