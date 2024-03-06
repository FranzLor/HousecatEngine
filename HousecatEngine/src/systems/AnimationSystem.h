#pragma once

#include "../ecs/ECS.h"

#include "../components/AnimationComponent.h"
#include "../components/MovementStateComponent.h"
#include "../components/SpriteComponent.h"


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