#pragma once

#include <memory>

#include <sol/sol.hpp>

#include "../utilities/SDLUtility.h"

#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"

class EditorUIRendering: public System {
private:
	int canvasWidth;
	int canvasHeight;
	int canvasPreviousWidth;
	int canvasPreviousHeight;

	int tileSize;
	int tilePrevSize;

	bool createTiles;
	bool removedTile;

	int gridX;
	int gridY;
	bool gridSnap;
	bool gridShow;

	bool isExit;
	

	std::shared_ptr<class EditorCanvas> canvas;
	std::shared_ptr<class EditorUIManager> editorUIManager;
	std::shared_ptr<class Mouse> mouse;
	std::unique_ptr<class EditManager> editManager;

	sol::state lua;

	const bool MouseOutOfBounds() const;

	void SetExit(bool exit) {
		isExit = exit;
	}

public:
	EditorUIRendering();
	~EditorUIRendering();

	void Update(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile,
		SDL_Event& event, const float& zoom, const float& dT);

	void RenderGrid(EditorRenderer& renderer, SDL_Rect& camera, const float& zoom);

	void CreateNewCanvas();

	void UpdateCanvas();

	void ClearCanvas();

	void ShowMouseLocation(SDL_Rect& mouseTile, SDL_Rect& camera);

	inline const bool& GetExit() const {
		return isExit;
	}

};

