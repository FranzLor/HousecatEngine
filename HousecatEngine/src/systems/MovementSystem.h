#pragma once

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"
#include "../events/CollisionEvent.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/SpriteComponent.h"

#include "../game/CollisionMap.h"

//----------------------------------------------------//
//                MOVEMENT SYSTEM                     //
// Manages the movement and collision interactions    //
// for entities with physical presence in the game.   //
//----------------------------------------------------//



class MovementSystem: public System {
public:
	MovementSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void ListenToEvents(const std::unique_ptr<EventManager>& eventManager) {
		eventManager->ListenToEvent<CollisionEvent>(this, &MovementSystem::HandleCollision);
	}

	void HandleCollision(CollisionEvent& event) {
		Entity a = event.a;
		Entity b = event.b;

		//npc flip
		if (a.HasGroup("npc") && b.HasGroup("barriers")) {
			EntityHitsBarrier(a, b);
		}
		if (a.HasGroup("barriers") && b.HasGroup("npc")) {
			EntityHitsBarrier(b, a);
		}
	}

	void EntityHitsBarrier(Entity entity, Entity barrier) {
		if (entity.HasComponent<RigidBodyComponent>()) {
			auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			//flip velocity and sprite horizontal
			if (rigidbody.velocity.x != 0) {
				rigidbody.velocity.x *= -1;
				sprite.flip = (sprite.flip == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
			}
			if (rigidbody.velocity.y != 0) {
				rigidbody.velocity.y *= -1;
				sprite.flip = (sprite.flip == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
			}
		}
	}

	void Update(double deltaTime) {
		for (auto entity : GetSystemEntities()) {
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
			//for player collision on collision map tiles
			bool hasBoxCollider = entity.HasComponent<BoxColliderComponent>();

			//calc init pos based on current velocity
			glm::vec2 initPosition = transform.position + glm::vec2(rigidbody.velocity.x * deltaTime, rigidbody.velocity.y * deltaTime);

			//for clamping within padded boundaries
			float maxPosX = (Game::mapWidth - Game::paddingRight) - transform.scale.x;
			float maxPosY = (Game::mapHeight - Game::paddingBottom) - transform.scale.y;

			initPosition.x = std::clamp(initPosition.x, static_cast<float>(Game::paddingLeft), maxPosX);
			initPosition.y = std::clamp(initPosition.y, static_cast<float>(Game::paddingTop), maxPosY);

			//tiles covered by the entity at init pos
			int minX = static_cast<int>(initPosition.x / (Game::tileSize * Game::tileScale));
			int maxX = static_cast<int>((initPosition.x + transform.scale.x * Game::tileSize) / (Game::tileSize * Game::tileScale));
			int minY = static_cast<int>(initPosition.y / (Game::tileSize * Game::tileScale));
			int maxY = static_cast<int>((initPosition.y + transform.scale.y * Game::tileSize) / (Game::tileSize * Game::tileScale));

			bool canMove = true;
			if (hasBoxCollider) {
				for (int x = minX; x <= maxX && canMove; x++) {
					for (int y = minY; y <= maxY && canMove; y++) {
						if (!CollisionMap::WalkableTiles(x, y)) {
							//nonwalkable
							canMove = false;
						}
					}
				}
			}
			
			if (canMove) {
				transform.position = initPosition;
			}
			else if (entity.HasTag("player")) {
				//player hits wall
				rigidbody.velocity.x = 0;
				rigidbody.velocity.y = 0;
			}

			//checks if outside the map boundaries, buffer margin forgives 200 px W/H
			int cullingMargin = 200;
			bool isEntityOutsideMap = (
				transform.position.x > Game::mapWidth + cullingMargin ||
				transform.position.x < -cullingMargin ||
				transform.position.y > Game::mapHeight + cullingMargin ||
				transform.position.y < -cullingMargin
			);

			if (!entity.HasTag("player") && isEntityOutsideMap) {
				entity.Kill();
			}
		}
	
	}

};




/**
 *
 * @class MovementSystem
 * @brief Manages the physics and movement of entities based on their velocity and interactions with the environment.
 *
 * This system updates the positions of entities based on their velocity while considering environmental
 * constraints like collisions with barriers and map boundaries. It handles basic physics by responding to
 * collisions, potentially reversing movement directions, and adjusting entity positions according to
 * walkable and non-walkable areas defined in the CollisionMap.
 *
 * Usage:
 * - This system should be added to your game engine to manage physical movement and collision handling.
 * - It must be updated regularly each frame to ensure entity movements are processed.
 * - It listens to collision events to handle interactions between entities dynamically during the game.
 *
 * Example:
 * 	housecat->AddSystem<MovementSystem>();
 * 
 *  Adding MovementSystem to the game using Housecat
 *
 * 	housecat->GetSystem<MovementSystem>().ListenToEvents(eventManager);
 * 
 *  Listening to events in your game 
 *
 * 	housecat->GetSystem<MovementSystem>().Update(deltaTime);
 * 
 *  Updating the MovementSystem each frame
 *
 * Key Methods:
 * - Update(deltaTime): Computes and updates the positions of entities based on their velocities and handles collisions.
 * - HandleCollision(event): Responds to collision events by adjusting entity velocities and positions.
 * - EntityHitsBarrier(entity, barrier): Adjusts entity movement when colliding with barriers to simulate physical responses.
 *
 * This system is critical for implementing responsive and realistic physics behavior in the game,
 * affecting gameplay through dynamic interaction and movement adjustments based on the game environment and entity interactions.
 * 
 */