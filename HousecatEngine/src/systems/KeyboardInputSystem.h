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


//----------------------------------------------------//
//                DAMAGE SYSTEM                       //
// Manages damage interactions between entities based //
//  on collision events and entity attributes.        //
//----------------------------------------------------//



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




/**
 *
 * @class DamageSystem
 * @brief Manages the application of damage and health modifications resulting from collisions in the game.
 *
 * DamageSystem listens for CollisionEvents and applies damage to entities based on their DamageAreaComponent
 * and HealthComponent. It checks if entities involved in the collision should receive damage, modifies their
 * health accordingly, and can trigger end-game scenarios such as game over or level completion based on health
 * depletion or specific collision events.
 *
 * Usage:
 * - Add this system to the game to manage all damage-related interactions.
 * - System uses the EventManager to listen for collision events and to respond appropriately.
 *
 * Example:
 * 	housecat->AddSystem<DamageSystem>(*this);
 * 
 *  Adding the DamageSystem to the game
 *
 * 	housecat->GetSystem<DamageSystem>().Update();
 * 
 *  Updating the DamageSystem in the game loop
 *
 * Key Methods:
 * - HandleCollision(event): Called when a CollisionEvent occurs, checks if damage should be applied and updates entity health.
 * - CanApplyDamage(entity): Checks if enough time has passed since the last damage was applied to an entity, preventing rapid re-damage.
 * - EntityOnDamageArea(area, entity): Applies damage to an entity and manages effects like flashing or sound effects.
 *
 * The DamageSystem is crucial for implementing interactive and responsive gameplay where entities can affect each other's
 * state through physical interactions or combat scenarios. It ensures the game's rules regarding health and damage are
 * consistently applied and manages the consequences of entity interactions.
 * 
 */