#pragma once

#include "../ecs/ECS.h"

#include "../components/BoxColliderComponent.h"
#include "../components/TransformComponent.h"

#include "../events/CollisionEvent.h"


//----------------------------------------------------//
//                COLLISION SYSTEM                    //
//  Handles the detection of collisions between       //
//  entities using axis-aligned bounding boxes (AABB).//
//----------------------------------------------------//



class CollisionSystem : public System {
public:
	CollisionSystem() {
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	//uses AABB collision algo design
	bool CheckCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {
		return (
			aX < bX + bW &&
			aX + aW > bX &&
			aY < bY + bH &&
			aY + aH > bY
		);
	}

	void Update(std::unique_ptr<EventManager>& eventManager) {
		auto entities = GetSystemEntities();

		//loop entities where system requires a components
		for (auto a = entities.begin(); a != entities.end(); a++) {
			Entity entityA = *a;

			auto transformA = entityA.GetComponent<TransformComponent>();
			auto colliderA = entityA.GetComponent<BoxColliderComponent>();

			//loop all that needs to be checked
			for (auto b = a; b != entities.end(); b++) {
				Entity entityB = *b;

				//bypass when its the same entity
				if (entityA == entityB) {
					continue;
				}

				auto transformB = entityB.GetComponent<TransformComponent>();
				auto colliderB = entityB.GetComponent<BoxColliderComponent>();

				bool hasCollided = CheckCollision(
					transformA.position.x + colliderA.offset.x,
					transformA.position.y + colliderA.offset.y,

					//account for scaling
					colliderA.width * transformA.scale.x,
					colliderA.height * transformA.scale.y,

					transformB.position.x + colliderB.offset.x,
					transformB.position.y + colliderB.offset.y,

					//account for scaling
					colliderB.width * transformB.scale.x,
					colliderB.height * transformB.scale.y
				);

				if (hasCollided) {
					//Logger::Log("Entity [" + std::to_string(entityA.GetID()) + "] Collided With [" + std::to_string(entityB.GetID()) + "]");
					eventManager->TriggerEvent<CollisionEvent>(entityA, entityB);
				}
			}
		}
	}
};




/**
 *
 * @class CollisionSystem
 * @brief Manages collision detection and response for entities with BoxColliderComponent and TransformComponent.
 *
 * This system utilizes the Axis-Aligned Bounding Box (AABB) algorithm to detect collisions between entities
 * in the game. When a collision is detected, it triggers a CollisionEvent, allowing other systems to handle
 * the collision effects such as damage, physics responses, or gameplay logic.
 *
 * Usage:
 * - Add this system to the game engine to handle collisions for entities that include physical interactions.
 * - Update this system every frame to check for and respond to collisions.
 *
 * Example:
 * 	housecat->AddSystem<CollisionSystem>();
 * 
 *  Adding CollisionSystem to the game project using housecat
 * 
 * 	housecat->GetSystem<CollisionSystem>().Update(eventManager);
 * 
 *  Updating the CollisionSystem each frame to check for collisions with the EventManager
 *
 * Key Methods:
 * - Update(eventManager): Checks for collisions between entities and triggers CollisionEvent for each detected collision.
 * - CheckCollision(aX, aY, aW, aH, bX, bY, bW, bH): Determines if two entities' bounding boxes are overlapping.
 *
 * This system is essential for games that require dynamic interaction between entities, ensuring that collisions
 * are handled efficiently and accurately. It forms the foundation for physical interactions within the game world.
 * 
 * Note:
 * - Use the EventManager to handle collision by listening and triggering responses.
 */