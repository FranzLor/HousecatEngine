#pragma once

#include "../ecs/ECS.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"

class MovementSystem: public System {
public:
	MovementSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
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

