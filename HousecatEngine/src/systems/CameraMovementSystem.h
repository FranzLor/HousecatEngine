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

			//center on entity + camera does not go beyond map
			if (transform.position.x + (camera.w / 2) < static_cast<float>(Game::mapWidth)) {
				camera.x = static_cast<int>(transform.position.x - Game::windowWidth / 2);
			}
			if (transform.position.y + (camera.h / 2) < static_cast<float>(Game::mapHeight)) {
				camera.y = static_cast<int>(transform.position.y - Game::windowHeight / 2);
			}

			//clamp the camera pos so it stays within the map
			//if padding removed
			camera.x = std::max(0, camera.x);
			camera.y = std::max(0, camera.y);

			camera.x = std::min(camera.x, Game::mapWidth - camera.w);
			camera.y = std::min(camera.y, Game::mapHeight - camera.h);
		}

	}
};

