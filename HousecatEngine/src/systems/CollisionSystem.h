#pragma once

#include "../ecs/ECS.h"

#include "../components/BoxColliderComponent.h"
#include "../components/TransformComponent.h"

#include "../events/CollisionEvent.h"

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
				//REMIND TESTING
				if (hasCollided) {
					Logger::Log("Entity [" + std::to_string(entityA.GetID()) + "] Collided With [" + std::to_string(entityB.GetID()) + "]");

					eventManager->TriggerEvent<CollisionEvent>(entityA, entityB);
				}
			}
		}
	}
};