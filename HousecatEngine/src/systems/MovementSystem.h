#pragma once

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"
#include "../events/CollisionEvent.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/SpriteComponent.h"

#include "../game/CollisionMap.h"

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
			auto& rigidbody = entity.GetComponent<RigidBodyComponent>(); // Removed const to modify if needed

			glm::vec2 initPosition = transform.position + glm::vec2(rigidbody.velocity.x * deltaTime, rigidbody.velocity.y * deltaTime);

			//prevent moving outside map bound
			if (entity.HasTag("player")) {
				float effectiveMinX = static_cast<float>(Game::paddingLeft);
				float effectiveMaxX = static_cast<float>(Game::mapWidth - Game::paddingRight);
				float effectiveMinY = static_cast<float>(Game::paddingTop);
				float effectiveMaxY = static_cast<float>(Game::mapHeight - Game::paddingBottom);

				initPosition.x = std::max(effectiveMinX, std::min(initPosition.x, effectiveMaxX));
				initPosition.y = std::max(effectiveMinY, std::min(initPosition.y, effectiveMaxY));
			}

			//calc the next pos tile indices, check if walkable
			int nextTileX = static_cast<int>(initPosition.x / (Game::tileSize * Game::tileScale));
			int nextTileY = static_cast<int>(initPosition.y / (Game::tileSize * Game::tileScale));

			bool canMoveX = CollisionMap::WalkableTiles(nextTileX, static_cast<int>(transform.position.y / (Game::tileSize * Game::tileScale)));
			bool canMoveY = CollisionMap::WalkableTiles(static_cast<int>(transform.position.x / (Game::tileSize * Game::tileScale)), nextTileY);

			//movement
			if (canMoveX && canMoveY) {
				transform.position = initPosition;
			}
			else if (canMoveX) {
				transform.position.x = initPosition.x;
			}
			else if (canMoveY) {
				transform.position.y = initPosition.y;
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

