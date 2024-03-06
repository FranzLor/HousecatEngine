#pragma once

#include <map>

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"
#include "../events/KeyPressedEvent.h"
#include "../events/KeyReleasedEvent.h"
#include "../events/Event.h"

#include "../components/UserControlComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/MovementStateComponent.h"

class KeyboardInputSystem : public System {
private:
	//tracks key states
	std::map<SDL_Keycode, bool> keyStates;

public:
	KeyboardInputSystem() {
		RequireComponent<UserControlComponent>();
		RequireComponent<RigidBodyComponent>();
		RequireComponent<SpriteComponent>();
	}

	void ListenToEvents(std::unique_ptr<EventManager>& eventManager) {
		eventManager->ListenToEvent<KeyPressedEvent>(this, &KeyboardInputSystem::KeyInput);
		eventManager->ListenToEvent<KeyReleasedEvent>(this, &KeyboardInputSystem::KeyRelease);
	}

	void KeyRelease(KeyReleasedEvent& event) {
		keyStates[event.keyReleasedSymbol] = false;
		UpdateMovementDirection();
	}

	void KeyInput(KeyPressedEvent& event) {
		keyStates[event.keyPressedSymbol] = true;
		UpdateMovementDirection();
		//REMIND testing convt to key input
		//std::string keyCode = std::to_string(event.keySymbol);
		//std::string keySymbol(1, event.keySymbol);
	}


	void UpdateMovementDirection() {
		for (auto entity : GetSystemEntities()) {
			const auto userControl = entity.GetComponent<UserControlComponent>();
			auto& movementState = entity.GetComponent<MovementStateComponent>();
			auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			movementState.isMoving = false;

			//velocity at zero to stop movement if no keys are pressed
			glm::vec2 newVelocity = glm::vec2(0, 0);

			if (keyStates[SDLK_w]) {
				movementState.isMoving = true;
				newVelocity = userControl.upDirection;
				sprite.srcRect.y = sprite.height * 0;
			}
			if (keyStates[SDLK_s]) {
				movementState.isMoving = true;

				newVelocity = userControl.downDirection;
				sprite.srcRect.y = sprite.height * 2;
			}
			if (keyStates[SDLK_a]) {
				movementState.isMoving = true;

				newVelocity = userControl.leftDirection;
				sprite.srcRect.y = sprite.height * 3;
			}
			if (keyStates[SDLK_d]) {
				movementState.isMoving = true;

				newVelocity = userControl.rightDirection;
				sprite.srcRect.y = sprite.height * 1;
			}

			rigidbody.velocity = newVelocity;

		}
	}
};