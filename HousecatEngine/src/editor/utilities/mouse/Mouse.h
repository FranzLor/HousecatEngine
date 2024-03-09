#pragma once

#include <glm/glm.hpp>
#include <string>

#include "../../utilities/SDLUtility.h"

#include "../../../ecs/ECS.h"
#include "../../../assetmanager/AssetManager.h"

#include "../../../components/TransformComponent.h"
#include "../../../components/SpriteComponent.h"

class Mouse {
private:
	int mousePosX;
	int mousePosY;
	glm::vec2 mouseRect;
	glm::vec2 mousePosTile;
	glm::vec2 mousePrevPosTile;
	glm::vec2 mousePosWindow;

	bool isLeftMouseButton;
	bool isMiddleMouseButton;
	bool isRightMouseButton;

	bool tileAdded;
	bool tileRemoved;
	int tileRecent;

	//canvas contorl
	int tileSize;
	int panX;
	int panY;
	float zoom;
	bool gridSnap;

	//mouse bounds
	bool isMouseOutOfBounds;
	const bool MouseOutOfBounds() const;


	//component management
	TransformComponent appliedTransform;
	TransformComponent removedTransform;

	SpriteComponent appliedSprite;
	SpriteComponent removedSprite;


	//mouse buttons SDL
	bool LeftMouseButton() {
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
	}
	bool MiddleMouseButton() {
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
	}
	bool RightMouseButton() {
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);
	}

public:
	Mouse();
	~Mouse() = default;

	//mouse 
	void MouseTile(EditorRenderer& renderer, const AssetManagerPtr& assetManger, SDL_Rect& camera, SDL_Rect& mouseTile);

	void CreateTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event);

	void UpdateMousePosition(const SDL_Rect& camera);

	void MousePanCamera(EditorRenderer& renderer, SDL_Rect& camera, const AssetManagerPtr& assetManager, const float& dT);

	//components
	void ApplyTransform(const int scaleX, const int scaley);

	void ApplySprite(const std::string& assetID, const int width, const int height, const int layer, const int srcRectX, const int srcRectY);

	//mouse edit
	inline const bool& TileAdded() const {
		return tileAdded;
	}
	inline const int& GetAddedTile() const {
		return tileRecent;
	}
	inline const void SetTileAdded(bool tile) {
		tileAdded = tile;
	}

	inline const bool& TileRemoved() const {
		return tileRemoved;
	}
	inline const int& GetRemovedTile() const {
		return tileRecent;
	}
	inline const void SetRemovedTile(bool tile) {
		tileRemoved = tile;

	}

	const TransformComponent& GetRemovedTransform() {
		return removedTransform;
	}
	const SpriteComponent& GetRemovedSprite() {
		return removedSprite;
	}
};

