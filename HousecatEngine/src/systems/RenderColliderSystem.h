#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../components/BoxColliderComponent.h"
#include "../components/TransformComponent.h"


//----------------------------------------------------//
//             RENDER COLLIDER SYSTEM                 //
// Visualizes colliders and debug grids in the game.  //
//----------------------------------------------------//



class RenderColliderSystem : public System {
private:
	bool isRendering = false;
public:
	RenderColliderSystem() {
		bool isRendering = false;
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(SDL_Renderer* renderer, SDL_Rect& camera) const {
		for (auto entity : GetSystemEntities()) {
			const auto collider = entity.GetComponent<BoxColliderComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();

			SDL_Rect colliderRect = {
				static_cast<int>(transform.position.x + collider.offset.x - camera.x),
				static_cast<int>(transform.position.y + collider.offset.y - camera.y),
				static_cast<int>(collider.width * transform.scale.x),
				static_cast<int>(collider.height * transform.scale.y)
			};

			//only show colliders in camera view
			if (colliderRect.x + colliderRect.w > 0 && colliderRect.x < camera.w &&
				colliderRect.y + colliderRect.h > 0 && colliderRect.y < camera.h) {
				SDL_RenderDrawRect(renderer, &colliderRect);
			}

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
	}

	void RenderDebugGrid(SDL_Renderer* renderer, SDL_Rect& camera, int tileWidth, int tileHeight, int windowWidth, int windowHeight) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		//calc init for grid lines on camera view
		int startX = camera.x - (camera.x % tileWidth);
		int startY = camera.y - (camera.y % tileHeight);

		//vertical lines
		for (int x = startX; x < camera.x + windowWidth; x += tileWidth) {
			//convert world coords to screen coords
			int screenX = x - camera.x;
			SDL_RenderDrawLine(renderer, screenX, 0, screenX, windowHeight);
		}

		//horizontal lines
		for (int y = startY; y < camera.y + windowHeight; y += tileHeight) {
			//ditto for y
			int screenY = y - camera.y;
			SDL_RenderDrawLine(renderer, 0, screenY, windowWidth, screenY);
		}
	}

	void ToggleRenderingState() {
		isRendering = !isRendering;
	}

	bool GetRenderingState() const {
		return isRendering;
	}
};




/**
 *
 * @class RenderColliderSystem
 * @brief A system for rendering collider outlines and debug grids to visualize the physical boundaries of entities.
 *
 * This system assists in debugging by allowing developers to visually confirm the extents and interactions
 * of colliders associated with entities. It draws rectangles around entities with BoxColliderComponent and
 * TransformComponent to show their bounding boxes in the game world relative to the camera view.
 *
 * Usage:
 * - This system should be added to your game if debugging visualizations are needed for development.
 * - It should be activated or deactivated through UI controls or developer inputs to toggle rendering of colliders.
 *
 * Example:
 * 	housecat->AddSystem<RenderColliderSystem>();
 * 
 *  Adding RenderColliderSystem to the game using Housecat
 *
 * 	if (isDebugging) {
 * 	    auto& renderColliderSystem = housecat->GetSystem<RenderColliderSystem>();
 * 	    if (renderColliderSystem.GetRenderingState()) {
 * 	        renderColliderSystem.ToggleRenderingState();
 * 	    }
 * 	}
 * 
 *  Toggling the collider rendering in response to a debug mode toggle
 *
 * Key Methods:
 * - Update(renderer, camera): Called within the rendering loop to draw collider outlines for visible entities.
 * - RenderDebugGrid(renderer, camera, tileWidth, tileHeight, windowWidth, windowHeight): Optionally draws a grid overlay
 *   for further spatial context in debugging modes.
 * - ToggleRenderingState(): Toggles the rendering state of colliders to either show or hide them.
 * - GetRenderingState(): Returns the current rendering state to determine if colliders are being shown.
 *
 * This system plays a crucial role in development phases, especially when fine-tuning physical interactions and ensuring
 * that entity boundaries are correctly set and respected within the game environment.
 * 
 * Note:
 * - This system should be called after the main Rendering System.
 */