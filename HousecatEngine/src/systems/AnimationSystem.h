#pragma once

#include "../ecs/ECS.h"

#include "../components/AnimationComponent.h"
#include "../components/MovementStateComponent.h"
#include "../components/SpriteComponent.h"


//--------------------------------------------------//
//                ANIMATION SYSTEM                  //
// Handles animation logic based on entity movement.//
//--------------------------------------------------//


class AnimationSystem : public System {
public:
	AnimationSystem() {
		RequireComponent<AnimationComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<MovementStateComponent>();
	}

	void Update() {
		for (auto entity : GetSystemEntities()) {
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& movementState = entity.GetComponent<MovementStateComponent>();
			
			if (movementState.isMoving == true) {
				animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeed / 1000) % animation.numFrames;
				//goes to the right of the src rect of sprite
				sprite.srcRect.x = animation.currentFrame * sprite.width;
			}
			else {
				sprite.srcRect.x = 0;
			}
		}
	}
};




/**
 *
 * @class AnimationSystem
 * @brief Manages the animation states of entities based on their movement states.
 *
 * This system updates the animation frames of entities that have AnimationComponent,
 * SpriteComponent, and MovementStateComponent. It ensures that each entity's sprite
 * is animated according to its movement, updating frames based on the elapsed time and
 * the defined frame speed in the AnimationComponent.
 *
 * Usage:
 * - This system must be added to your game project's system manager during initialization.
 * - It should be updated each frame to reflect the current animations of the entities.
 *
 * Example:
 * 	housecat->AddSystem<AnimationSystem>();
 * 
 *  Adding the AnimationSystem in a game project by calling housecat
 *
 * 	housecat->GetSystem<AnimationSystem>().Update();
 * 
 *  Updating the AnimationSystem in the game loop
 *
 * Key Methods:
 * - Update(): Called on each frame to update the animation frames of all registered entities based
 *   on their movement states.
 *
 * This system is crucial for visually representing the dynamic states of entities in the game,
 * contributing to a lively and responsive game environment.
 * 
 */