#pragma once

#include <glm/glm.hpp>
#include <string>

#include "../../utilities/SDLUtility.h"

#include "../../../ecs/ECS.h"
#include "../../../assetmanager/AssetManager.h"
#include "../../ui/EditorCanvas.h"

#include "../../../components/TransformComponent.h"
#include "../../../components/SpriteComponent.h"
#include "../../../components/BoxColliderComponent.h"


//-----------------------------------------------------//
//                       Mouse                         //
// Manages the mouse interactions for tile editing in  //
// the editor environment, including creation, removal,//
// and manipulation of tiles via mouse actions.        //
//-----------------------------------------------------//


//used for defining if tiles
//for tile checking method
enum class TileCheckResult {
	NoTile,
	DifferentTile,
	ExactTile
};


class Mouse {
private:
	int mousePosX;
	int mousePosY;
	glm::vec2 mouseRect;
	glm::vec2 mousePosTile;
	glm::vec2 mousePrevPosTile;
	glm::vec2 mousePosWindow;
	bool isMouseOutOfBounds;

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

	bool isCollider;

	//component management
	TransformComponent appliedTransform;
	TransformComponent removedTransform;

	SpriteComponent appliedSprite;
	SpriteComponent removedSprite;

	BoxColliderComponent appliedCollider;
	BoxColliderComponent removedCollider;


	//mouse buttons SDL
	bool LeftMouseButton() {
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
	}
	bool MiddleMouseButton() {
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
	}

	//right click does not work
	//IDK WTF
	/*bool RightMouseButton() {
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);
	}*/

public:
	Mouse();
	~Mouse() = default;


	//mouse 
	void MouseTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, bool collider = false);

	void CreateTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event);

	void RemoveTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event);

	void FillTiles(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event, const EditorCanvas& canvas);

	void CreateCollider(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event);

	//TODO
	//void FillTile(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event);

	bool MultiTile(const glm::vec2& pos);

	void UpdateMousePosition(const SDL_Rect& camera);

	void MousePanCamera(EditorRenderer& renderer, SDL_Rect& camera, const AssetManagerPtr& assetManager, const float& dT);


	//mouse bounds
	const bool MouseOutOfBounds() const;

	inline const glm::vec2& GetMousePosition() const {
		return mousePosWindow;
	}

	inline const glm::vec2& GetMouseRect() const {
		return mouseRect;
	}

	inline void MouseOverWindow(bool isOver) {
		isMouseOutOfBounds = isOver;
	}

	inline void SetMouseTileRect(int mouseRectX, int mouseRectY) {
		mouseRect = glm::vec2(mouseRectX, mouseRectY);
	}



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

	//grid checking
	TileCheckResult TileExistsAtPosition(int x, int y);


	//update
	inline void UpdateZoom(const float& mouseZoom) {
		zoom = mouseZoom;
	}

	inline void UpdateGridSize(const int& gridSize) {
		tileSize = gridSize;
	}

	

	//grid
	inline void SetGridSnap(bool snap) {
		gridSnap = snap;
	}


	//collder
	inline void SetCollider(bool collider) {
		isCollider = collider;
	}



	//components
	void ApplyTransform(const int scaleX, const int scaleY);

	void ApplySprite(const std::string& assetID, const int width, const int height, const int layer, const int srcRectX, const int srcRectY);

	void ApplyBoxCollider(const int width, const int height, const int offsetX, const int offsetY);

	

	const TransformComponent& GetRemovedTransform() {
		return removedTransform;
	}
	const SpriteComponent& GetRemovedSprite() {
		return removedSprite;
	}
	const BoxColliderComponent& GetRemovedCollider() {
		return removedCollider;
	}


};




/**
 * @file Mouse.h
 * @brief Handles mouse-based tile editing operations in the editor.
 *
 * The Mouse class is integral to the editor, allowing the user to interact directly
 * with the canvas via the mouse for operations like placing, deleting, and filling
 * tiles. It integrates deeply with the AssetManager to manage tile textures and with
 * the ECS to handle tile entities.
 *
 * Key Functionalities:
 * - MouseTile: Visualize potential tile placements based on current mouse position.
 * - CreateTile: Place a new tile at the mouse location.
 * - RemoveTile: Remove a tile at the mouse location.
 * - FillTiles: Fill an area with tiles based on specific conditions.
 * - UpdateMousePosition: Update mouse position relative to the camera and scaling.
 * - MousePanCamera: Handle camera panning via mouse dragging.
 *
 * The class also supports undo/redo functionalities indirectly by managing states
 * that can be captured by command objects (not implemented here).
 */