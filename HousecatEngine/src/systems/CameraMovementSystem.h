#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../components/CameraComponent.h"
#include "../components/TransformComponent.h"

class CameraMovementSystem : public System {
public:
	CameraMovementSystem() {
		RequireComponent<CameraComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			auto& transform = entity.GetComponent<TransformComponent>();

			if (transform.position.x + (camera.w / 2) < static_cast<float>(Game::mapWidth)) {
				camera.x = static_cast<int>(transform.position.x - (Game::windowWidth / 2));

			}
			if (transform.position.y + (camera.h / 2) < static_cast<float>(Game::mapHeight)) {
				camera.y = static_cast<int>(transform.position.y - (Game::windowHeight / 2));

			}
			camera.x = camera.x < 0 ? 0 : camera.x;
			camera.y = camera.y < 0 ? 0 : camera.y;

			camera.x = camera.x > camera.w ? camera.w : camera.x;
			camera.y = camera.y > camera.h ? camera.h : camera.y;

		}
	}
};