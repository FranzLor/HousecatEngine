#pragma once

#include <SDL.h>

#include "../ecs/ECS.h"

#include "../components/CameraComponent.h"
#include "../components/TransformComponent.h"


//--------------------------------------------------//
//              CAMERA MOVEMENT SYSTEM              //
//  Manages dynamic camera positioning based on     //
//  the position of entities within the game world. //
//--------------------------------------------------//



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




/**
 *
 * @class CameraMovementSystem
 * @brief Controls the camera's position in the game to follow entities or focus areas.
 *
 * This system adjusts the game camera to follow entities that have both a CameraComponent
 * and a TransformComponent, ensuring the camera smoothly tracks these entities as they move
 * through the game environment. It also handles the camera's bounds to ensure it does not
 * venture outside the predefined game map limits.
 *
 * Usage:
 * - This system should be added to your game project's system manager at initialization.
 * - It needs to be updated every frame to adjust the camera position based on the target
 *   entity's movements and the layout of the game environment.
 *
 * Example:
 * 	housecat->AddSystem<CameraMovementSystem>();
 * 
 *  Adding the CameraMovementSystem to the game project using housecat
 *
 * 	SDL_Rect camera = {0, 0, 640, 480};
 * 	housecat->GetSystem<CameraMovementSystem>().Update(camera);
 * 
 *  Updating the CameraMovementSystem each frame
 *
 * Key Methods:
 * - Update(camera): Adjusts the camera's position based on the entity's current position,
 *   ensuring the entity is centered within the camera's view and the camera stays within
 *   the allowable map boundaries.
 *
 * This system is important for creating a dynamic player experience by focusing
 * the player's view on relevant game activities, adapting to player movements and actions.
 * 
 */