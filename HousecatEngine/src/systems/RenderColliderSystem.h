#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../components/BoxColliderComponent.h"
#include "../components/TransformComponent.h"

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