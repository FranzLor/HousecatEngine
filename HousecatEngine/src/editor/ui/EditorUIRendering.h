#pragma once

#include <memory>

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

	std::shared_ptr<class EditorCanvas> canvas;
	std::shared_ptr<class EditorUIManager> editorUIManager;
	std::shared_ptr<class Mouse> mouse;
	std::unique_ptr<class EditManager> editManager;

	const bool MouseOutOfBounds() const;
public:
	EditorUIRendering();
	~EditorUIRendering();

	void Update(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile,
		SDL_Event& event, const float& zoom, const float& dT);

	void RenderGrid(EditorRenderer& renderer, SDL_Rect& camera, const float& zoom);

	void CreateNewCanvas();

	void UpdateCanvas();

	void ShowMouseLocation(SDL_Rect& mouseTile, SDL_Rect& camera);


};

