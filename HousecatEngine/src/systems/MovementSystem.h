#pragma once

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"
#include "../events/CollisionEvent.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/SpriteComponent.h"

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
			const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

			transform.position.x += static_cast<float>(rigidbody.velocity.x * deltaTime);
			transform.position.y += static_cast<float>(rigidbody.velocity.y * deltaTime);
		
			//prevent player form moving outside map
			if (entity.HasTag("player")) {
				//adjust padding for map (-5 on edge)
				int paddingLeft = -5;
				int paddingRight = -5;
				int paddingTop = -5;
				int paddingBottom = -5;

				paddingLeft *= static_cast<int>(transform.scale.x);
				paddingRight *= static_cast<int>(transform.scale.x);
				paddingTop *= static_cast<int>(transform.scale.y);
				paddingBottom *= static_cast<int>(transform.scale.y);

				//update position within boundaries
				transform.position.x = std::max(static_cast<float>(paddingLeft), std::min(transform.position.x, static_cast<float>(Game::mapWidth - paddingRight)));
				transform.position.y = std::max(static_cast<float>(paddingTop), std::min(transform.position.y, static_cast<float>(Game::mapHeight - paddingBottom)));
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

