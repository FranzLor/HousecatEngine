#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../components/BoxColliderComponent.h"
#include "../components/TransformComponent.h"

class RenderColliderSystem : public System {
public:
	RenderColliderSystem() {
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	//TODO
	//account for entity scale 
	void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			const auto collider = entity.GetComponent<BoxColliderComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();

			SDL_Rect colliderRect = {
				static_cast<int>(transform.position.x + collider.offset.x - camera.x),
				static_cast<int>(transform.position.y + collider.offset.y - camera.y),
				static_cast<int>(collider.width * transform.scale.x),
				static_cast<int>(collider.height * transform.scale.y)
			};

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &colliderRect);
		}
	}
};