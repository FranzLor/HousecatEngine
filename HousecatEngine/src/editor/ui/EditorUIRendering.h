#pragma once

#include <memory>

#include <sol/sol.hpp>

#include "../utilities/SDLUtility.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"


//-----------------------------------------------------//
//                  EditorUIRendering                  //
//   Handles rendering and updating of UI elements in  //
//   the Housecat game editor. It manages the canvas,  //
//   tile settings, and user interactions for editing  //
//   the game environment.                             //
//-----------------------------------------------------//

class EditorUIRendering : public System {
private:
	int canvasWidth;
	int canvasHeight;
	int canvasPreviousWidth;
	int canvasPreviousHeight;

	bool isTilesetLoaded;

	int tileSize;
	int tilePrevSize;

	bool createTiles;
	bool removedTile;

	int gridX;
	int gridY;
	bool gridSnap;
	bool gridShow;

	bool isClearPopup;
	bool isCleared;

	bool isDarkMode;

	bool isExit;


	std::shared_ptr<class EditorCanvas> canvas;
	std::shared_ptr<class EditorUIManager> editorUIManager;
	std::shared_ptr<class Mouse> mouse;
	std::unique_ptr<class EditManager> editManager;

	sol::state lua;

	const bool MouseOutOfBounds() const;

	void SetDarkMode(bool darkMode) {
		isDarkMode = darkMode;
	}

	void SetExit(bool exit) {
		isExit = exit;
	}

	void SetTilesetLoaded(bool loaded) {
		isTilesetLoaded = loaded;
	}

public:
	EditorUIRendering();
	~EditorUIRendering();

	void Update(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile,
		SDL_Event& event, const float& zoom, const float& dT);

	void RenderGrid(EditorRenderer& renderer, SDL_Rect& camera, const float& zoom);

	void CreateNewCanvas();

	void UpdateCanvas();

	void ClearPopup();

	void ClearCanvas();

	void ShowMouseLocation(SDL_Rect& mouseTile, SDL_Rect& camera);

	inline const bool& GetTileset() const {
		return isTilesetLoaded;
	}

	inline const bool& GetDarkMode() const {
		return isDarkMode;
	}

	inline const bool& GetExit() const {
		return isExit;
	}


};



/**
 * @file EditorUIRendering.h
 * @brief Handles rendering and UI updates in the Housecat game editor.
 *
 * The EditorUIRendering class extends from the System class, integrating with the entity-component system
 * to provide visual updates and interact with the game editor's functionalities. It manages the rendering
 * of grids, updating of canvas dimensions, and the interactions for creating, removing, or modifying tiles.
 * This class also interfaces with the EditorUIManager for managing UI states and interactions.
 *
 * Key functionalities include:
 * - Rendering grid lines and the editor's canvas.
 * - Managing canvas size and tile settings.
 * - Handling user input for direct tile manipulation.
 * - Providing visual feedback for mouse location and tile attributes.
 */